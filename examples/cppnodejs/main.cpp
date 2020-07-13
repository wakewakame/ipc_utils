#include <string>

#include <napi.h>

#define BOOST_DATE_TIME_NO_LIB
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

struct Data {
	int a;
};

Napi::Value Method(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  std::string key = "hogehoge";
  boost::interprocess::message_queue::remove(key.c_str());
  boost::interprocess::message_queue receiver(boost::interprocess::create_only, key.c_str(), 1, sizeof(Data));

  Data message;
  unsigned long recv_size;
  unsigned priority;
  receiver.receive(&message, sizeof(Data), recv_size, priority);

  return Napi::Number::New(env, message.a);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "receive"),
              Napi::Function::New(env, Method));
  return exports;
}

NODE_API_MODULE(addon, Init)