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
	boost::interprocess::message_queue sender(boost::interprocess::open_only, key.c_str());
	Data data;
	data.a = 135;
	std::cout << "sender : " << data.a << std::endl;
	sender.send(&data, sizeof(Data), 0);

	return 0;
}
