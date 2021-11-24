#include "react-native-jsi-test.h"
#include <thread>
#include <map>

static std::shared_ptr <CallInvoker> globalCallInvoker;

static Runtime *globaRuntime;

static std::shared_ptr <Function> globalOnMessageCallback;

static std::map <int, std::shared_ptr <Function>> globalCallbacksStore;

static int callbackId = 0;

namespace example {
void install(Runtime &jsiRuntime, std::shared_ptr <CallInvoker> callInvoker) {
	globalCallInvoker = callInvoker;
	globaRuntime = &jsiRuntime;
	globalOnMessageCallback = NULL;
	globalCallbacksStore = std::map<int, std::shared_ptr <Function>>();
	
	std::shared_ptr <UtilsTurboModule> nativeModule =
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


static Value helloWorld(Runtime &rt, TurboModule &turboModule,
						const Value *args, size_t arg_count) {
	String string = String::createFromUtf8(rt, "helloworld");
	
	globalOnMessageCallback = std::make_shared<Function>(args[0].getObject(rt).getFunction(rt));
	
	std::thread th{[]() {
		LOG("BEFORE SLEEP");
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		LOG("AFTER SLEEP");
		LOG("1");
		
		if (globalOnMessageCallback) {
			globalCallInvoker->invokeAsync([]() {
				String string = String::createFromUtf8(*globaRuntime, "helloworld");
				globalOnMessageCallback->call(*globaRuntime, string);
			});
		}
	}
	};
	
	th.detach();
	
	return Value::null();
};

static Value send(Runtime &rt, TurboModule &turboModule,
				  const Value *args, size_t arg_count) {
	callbackId++;
	
	globalCallbacksStore[callbackId] = std::make_shared<Function>(args[0].getObject(rt).getFunction(rt));
	
	int currentCallbackId = callbackId;
	
	std::thread th{[currentCallbackId]() {
		LOG("BEFORE SLEEP");
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		LOG("AFTER SLEEP");
		LOG("1");
		
		globalCallInvoker->invokeAsync([currentCallbackId]() {
			if(globalCallbacksStore[currentCallbackId]){
				String string = String::createFromUtf8(*globaRuntime, "send result");
				globalCallbacksStore[currentCallbackId]->call(*globaRuntime, string);
			}
		});
	}
	};
	
	th.detach();
	
	return Value::null();
};

TurboUtilsSpecJSI::TurboUtilsSpecJSI(std::shared_ptr <CallInvoker> jsInvoker) : TurboModule(
																							"exampleModule", jsInvoker) {
																								//here we assign our TurboModule object properties
																								methodMap_["helloWorld"] = MethodMetadata{0, helloWorld};
																								methodMap_["send"] = MethodMetadata{0, send};
																							}
}
