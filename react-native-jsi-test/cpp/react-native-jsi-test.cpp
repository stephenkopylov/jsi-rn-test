#include "react-native-jsi-test.h"
#include <thread>

namespace example {
int helloWorld(float a) {
	return a;
}

void install(Runtime & jsiRuntime) {}

void install(Runtime & jsiRuntime, CallInvoker &callInvoker) {
	auto helloWorld = Function::createFromHostFunction(jsiRuntime, PropNameID::forAscii(jsiRuntime, "helloWorld"), 0,[&callInvoker](Runtime & runtime,
																														const Value & thisValue, const Value * arguments, size_t count) -> Value {

		auto callback = std::make_shared<Value>((arguments[0].asObject(runtime)));

		std::thread th { [callback, &runtime, &callInvoker](){
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));

			callInvoker.invokeAsync([callback, &runtime]() {
				string helloworld = "helloworld";
				callback->asObject(runtime).asFunction(runtime).call(runtime, String::createFromUtf8(runtime, helloworld));
			});
		}};

		th.detach();

		return Value::null();
	});

	jsiRuntime.global().setProperty(jsiRuntime, "helloWorld", move(helloWorld));
}
}
