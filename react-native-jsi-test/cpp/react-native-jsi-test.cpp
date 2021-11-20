#include "react-native-jsi-test.h"
#include <thread>

namespace example {
void install(Runtime & jsiRuntime, std::shared_ptr<CallInvoker> callInvoker){

	std::shared_ptr<UtilsTurboModule> nativeModule =
	std::make_shared<UtilsTurboModule>(callInvoker);

	jsiRuntime.global().setProperty(jsiRuntime,
									PropNameID::forAscii(jsiRuntime, "exampleModule"),
									Object::createFromHostObject(jsiRuntime, nativeModule));

	//	auto helloWorld = Function::createFromHostFunction(jsiRuntime, PropNameID::forAscii(jsiRuntime, "helloWorld"), 0,[&callInvoker](Runtime & runtime,
	//																																	const Value & thisValue, const Value * arguments, size_t count) -> Value {
	//
	//		auto callback = std::make_shared<Value>((arguments[0].asObject(runtime)));
	//
	//		std::thread th { [callback, &runtime, &callInvoker](){
	//			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//
	//			CallInvoker *invoker = callInvoker.get();
	//
	//			invoker->invokeAsync([](){
	//
	//			});
	//
	//			//			*callInvoker->invokeAsync([callback, &runtime]() {
	//			//				string helloworld = "helloworld";
	//			//				callback->asObject(runtime).asFunction(runtime).call(runtime, String::createFromUtf8(runtime, helloworld));
	//			//			});
	//		}};
	//
	//		th.detach();
	//
	//		return Value::null();
	//	});

	//	jsiRuntime.global().setProperty(jsiRuntime, "helloWorld", move(helloWorld));
}


static Value _helloWorld(Runtime &rt, TurboModule &turboModule,
						 const Value *args, size_t arg_count) {

	auto callback = std::make_shared<Value>((args[0].getObject(rt)));

	std::thread th { [&rt, &turboModule, &callback](){
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			if(turboModule.jsInvoker_!=nullptr){
				try {
				const auto callInvoker = dynamic_cast<TurboUtilsSpecJSI *>(&turboModule)->jsInvoker_;
				//
				//			callInvoker->invokeAsync([&rt, &callback]() {
				//				string helloworld = "helloworld";
				//
				//				callback->getObject(rt).asFunction(rt).call(rt, String::createFromUtf8(rt, helloworld));
				//			});
				} catch (exception e) {

				}
			}
	}};

	th.detach();

	return Value::null();
};

TurboUtilsSpecJSI::TurboUtilsSpecJSI(std::shared_ptr<CallInvoker> jsInvoker): TurboModule("exampleModule", jsInvoker) {
	//here we assign our TurboModule object properties
	methodMap_["helloWorld"] = MethodMetadata{0, _helloWorld};
}

//String UtilsTurboModule::nativeGreeting(Runtime &rt, const String &name) {
//	return String::createFromUtf8(rt, "123123");
//}
//
//Value UtilsTurboModule::nativeSumSquares(Runtime &rt, double a, double b) {
//	return Value::null();
//}

}
