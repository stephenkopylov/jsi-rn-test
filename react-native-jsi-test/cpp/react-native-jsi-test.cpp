#include "react-native-jsi-test.h"

namespace example {
	int helloWorld(float a) {
		return a;
	}

void install(Runtime & jsiRuntime) {
	auto helloWorld = Function::createFromHostFunction(jsiRuntime, PropNameID::forAscii(jsiRuntime, "helloWorld"), 0,[](Runtime & runtime,
		const Value & thisValue, const Value * arguments, size_t count) -> Value {

		int x = arguments[0].getNumber();
		
		int y = arguments[1].getNumber();
		
		int z = x + y;

		string helloworld = "helloworld";

		arguments[2].getObject(runtime).getFunction(runtime).call(runtime, z);

		return Value(runtime, String::createFromUtf8(runtime, helloworld));
	});

	jsiRuntime.global().setProperty(jsiRuntime, "helloWorld", move(helloWorld));
}
}
