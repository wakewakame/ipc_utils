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
	boost::interprocess::message_queue::remove(key.c_str());
	boost::interprocess::message_queue receiver(boost::interprocess::create_only, key.c_str(), 10, sizeof(Data));
	
	Data message;
	unsigned long recv_size;
	unsigned priority;
	receiver.receive(&message, sizeof(Data), recv_size, priority);
	std::cout << "receiver : " << message.a << std::endl;

	boost::interprocess::message_queue::remove(key.c_str());

	return 0;
}
