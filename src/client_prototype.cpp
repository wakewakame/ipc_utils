#include <iostream>
#include <string>
#include <memory>
#include <vector>

#define BOOST_DATE_TIME_NO_LIB
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

struct SendMessage { int a; };
struct ReceiveMessage { int a; };

int init(const std::string& receiver_uuid, const std::string& sender_uuid) {
	try {
		boost::interprocess::message_queue receiver(boost::interprocess::open_only, receiver_uuid.c_str());
		boost::interprocess::message_queue sender(boost::interprocess::open_only, sender_uuid.c_str());

		// メインループ
		while(is_running(pid)) {
			// 受信
			ReceiveMessage received_message;
			unsigned long recv_size;
			unsigned priority;
			receive_message_queue.receive(&received_message, sizeof(ReceiveMessage), recv_size, priority);

			// ごにょごにょ

			// 送信
			SendMessage message;
			sender_message_queue.send(&message, sizeof(SendMessage), 0);
		}
	}
	catch(const std::???& e) {

	}
	
	return 0;
}