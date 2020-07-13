#include <iostream>
#include <string>
#include <thread>

#define BOOST_DATE_TIME_NO_LIB
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

struct Data {
	int a;
};

int main() {
	std::string key = "hogehoge";

	boost::interprocess::message_queue receiver(boost::interprocess::create_only, key.c_str(), 1, sizeof(Data));
	boost::interprocess::message_queue sender(boost::interprocess::open_only, key.c_str());

	{
		std::thread th([&]{
			Data message;
			unsigned long long recv_size;
			unsigned priority;
			//receiver.receive(&message, sizeof(Data), recv_size, priority);
			boost::posix_time::ptime timeout = boost::posix_time::microsec_clock::universal_time() + boost::posix_time::milliseconds(100);
			if (receiver.timed_receive(&message, sizeof(Data), recv_size, priority, timeout)) {
				std::cout << "receiver : " << message.a << std::endl;
			}
			else {
				std::cout << "receiver : timeout" << std::endl;
			}
		});
		Data data;
		data.a = 135;
		std::cout << "sender : " << data.a << std::endl;
		sender.send(&data, sizeof(Data), 0);
		th.join();
	}

	{
		std::thread th([&]{
			Data message;
			unsigned long long recv_size;
			unsigned priority;
			//sender.receive(&message, sizeof(Data), recv_size, priority);
			boost::posix_time::ptime timeout = boost::posix_time::microsec_clock::universal_time() + boost::posix_time::milliseconds(100);
			if (sender.timed_receive(&message, sizeof(Data), recv_size, priority, timeout)) {
				std::cout << "sender : " << message.a << std::endl;
			}
			else {
				std::cout << "sender : timeout" << std::endl;
			}
		});
		Data data;
		data.a = 92;
		std::cout << "receiver : " << data.a << std::endl;
		receiver.send(&data, sizeof(Data), 0);
		th.join();
	}

	boost::interprocess::message_queue::remove(key.c_str());

	return 0;
}
