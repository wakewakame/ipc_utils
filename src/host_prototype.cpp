#include <iostream>
#include <string>
#include <memory>
#include <vector>

#define BOOST_DATE_TIME_NO_LIB
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

struct SendMessage { int a; };
struct ReceiveMessage { int a; };
std::string generate_uuid4();
int exec_program(const std::string& file, const std::vector<std::string>>& args);
int close_program(int pid);
int is_running(int pid);
int is_freeze(int pid);
int generate_message_queue(
	std::string& uuid,
	std::unique_ptr<boost::interprocess::message_queue>& message_queue,
	size_t size,
	const size_t queue_size = 1
) {
	uuid = "";  // message_queueの名前
	const size_t try_count = 10;  // uuinジャンケンであいこが許される回数
	// uuidジャンケンでtry_count回あいこになったら異常終了
	for(size_t i = 0; i < try_count; i++) {
		uuid = generate_uuid4();
		try {
			message_queue = std::make_unique<boost::interprocess::message_queue>(
				boost::interprocess::create_only, uuid.c_str(), queue_size, size
			);
		}
		catch(const std::???& e) {
			// uuidジャンケンでtry_count回あいこになってしまったとき
			if (i + 1 == try_count) {
				// ERROR: FAILED TO MAKE MESSAGE QUEUE!!!
				return 1;
			}
		}
	}
	return 0;
}

int main() {
	// senderのmessage_queueの生成
	std::string sender_uuid;
	std::unique_ptr<boost::interprocess::message_queue> sender_message_queue;
	if (generate_message_queue(sender_uuid, sender_message_queue, sizeof(SendMessage))) return 1;

	// receiverのmessage_queueの生成
	std::string receive_uuid;
	std::unique_ptr<boost::interprocess::message_queue> receive_message_queue;
	if (generate_message_queue(receive_uuid, receive_message_queue, sizeof(ReceiveMessage))) return 1;

	// node.jsプロセスの実行
	std::string js_filepath = "start_ipc.js";
	std::vector<std::string> node_args;
	node_args.push_back(js_filepath);
	node_args.push_back(sender_uuid);
	node_args.push_back(receive_uuid);
	int pid = exec_program("node", node_args);

	// メインループ
	while(is_running(pid) && !is_freeze(pid)) {
		// 送信
		SendMessage send_message;
		sender_message_queue.send(&send_message, sizeof(SendMessage), 0);

		// 受信
		ReceiveMessage received_message;
		unsigned long recv_size;
		unsigned priority;
		boost::posix_time::ptime timeout = boost::posix_time::microsec_clock::universal_time() + boost::posix_time::milliseconds(5000);
		if (receive_message_queue.timed_receive(&received_message, sizeof(ReceiveMessage), recv_size, priority, timeout)) {
			// do something
		}

		// ごにょごにょ
	}

	// 後片付け
	if (is_running(pid)) { close_program(pid); }
	boost::interprocess::message_queue::remove(sender_uuid.c_str());
	boost::interprocess::message_queue::remove(receive_uuid.c_str());
	
	return 0;
}