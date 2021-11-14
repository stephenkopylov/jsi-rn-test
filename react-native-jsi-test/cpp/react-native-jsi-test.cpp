#include "react-native-jsi-test.h"

namespace example {
	int helloWorld(float a) {
		return a;
	}

void install(Runtime & jsiRuntime) {
	auto helloWorld = Function::createFromHostFunction(jsiRuntime, PropNameID::forAscii(jsiRuntime, "helloWorld"), 0,[](Runtime & runtime,
		const Value & thisValue,
			const Value * arguments, size_t count) -> Value {

		string x = arguments[0].getString(runtime).utf8(runtime);

		string helloworld = "helloworld";

		arguments[1].getObject(runtime).getFunction(runtime).call(runtime, x);

		return Value(runtime, String::createFromUtf8(runtime, helloworld));
	});

	jsiRuntime.global().setProperty(jsiRuntime, "helloWorld", move(helloWorld));
}
}
