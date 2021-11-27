#include "react-native-jsi-test-view.h"
#include <thread>
#include <map>
#include "JSIObjectToRapidJsonConverter.h"

static std::shared_ptr <CallInvoker> globalCallInvoker;

static Runtime *globaRuntime;

static std::shared_ptr <Function> globalOnMessageCallback;

static std::map <int, std::shared_ptr <Function>> globalCallbacksStore;

static int callbackId = 0;

static std::shared_ptr <Function> globalParse;

static std::shared_ptr <Function> globalStringify;

namespace exampleView {
void install(Runtime &jsiRuntime, std::shared_ptr <CallInvoker> callInvoker) {
	globalCallInvoker = callInvoker;
	globaRuntime = &jsiRuntime;
	globalOnMessageCallback = NULL;
	globalCallbacksStore = std::map<int, std::shared_ptr <Function>>();
	
	std::shared_ptr <UtilsTurboModule> nativeModule =
	std::make_shared<UtilsTurboModule>(callInvoker);
	
	//	Function stringifyObject =
	
	globalParse = std::make_shared<Function>(jsiRuntime.global()
												 .getPropertyAsObject(jsiRuntime, "JSON")
												 .getPropertyAsFunction(jsiRuntime, "parse"));
	
	globalStringify = std::make_shared<Function>(jsiRuntime.global()
												 .getPropertyAsObject(jsiRuntime, "JSON")
												 .getPropertyAsFunction(jsiRuntime, "stringify"));
	
	jsiRuntime.global().setProperty(jsiRuntime,
									PropNameID::forAscii(jsiRuntime, "exampleViewModule"),
									Object::createFromHostObject(jsiRuntime, nativeModule));
}


static Value helloWorld(Runtime &rt, TurboModule &turboModule,
						const Value *args, size_t arg_count) {//one callback test
	String string = String::createFromUtf8(rt, "helloworld");
	
	globalOnMessageCallback = std::make_shared<Function>(args[0].getObject(rt).getFunction(rt));
	
	std::thread th{[]() {
		LOG("BEFORE SLEEP");
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		LOG("AFTER SLEEP");
		LOG("1");
		
		if (globalOnMessageCallback) {
			globalCallInvoker->invokeAsync([]() {
				String string = String::createFromUtf8(*globaRuntime, "helloworld result");
				globalOnMessageCallback->call(*globaRuntime, string);
			});
		}
	}
	};
	
	th.detach();
	
	return Value::null();
};

static Value send(Runtime &rt, TurboModule &turboModule,
				  const Value *args, size_t arg_count) {//multiple callbacks test
	callbackId++;
	
	globalCallbacksStore[callbackId] = std::make_shared<Function>(args[0].getObject(rt).getFunction(rt));
	
	int currentCallbackId = callbackId;
	
	std::thread th{[currentCallbackId]() {
		LOG("BEFORE SLEEP");
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		LOG("AFTER SLEEP");
		LOG("1");
		
		globalCallInvoker->invokeAsync([currentCallbackId]() {
			const char *message = "{\"test\":123}";
			
			Value object = Value::createFromJsonUtf8(*globaRuntime, (const unsigned char *)message, strlen(message));
			
			if(globalCallbacksStore[currentCallbackId]){
				globalCallbacksStore[currentCallbackId]->call(*globaRuntime, object);
			}
		});
	}
	};
	
	th.detach();
	
	return Value::null();
};

static Value testJsonParseCPP(Runtime &rt, TurboModule &turboModule,
							  const Value *args, size_t arg_count) {
	callbackId++;
	
	Object object = args[0].getObject(rt);
	
//	rapidjson::Document document = JSIObjectToRapidJsonConverter::convert(rt, object);
	
//	std::string document = JSIObjectToRapidJsonConverter::convertToString(rt, object);
	
	const char *str = "123";
	
	return Value::createFromJsonUtf8(rt, (const unsigned char *)str, strlen(str));
};

static Value testJsonNativeParse(Runtime &rt, TurboModule &turboModule,
								 const Value *args, size_t arg_count) {
	callbackId++;
	
//	Object object = args[0].getObject(rt);
	
	std::string jsString = globalStringify->call(rt, args[0]).asString(rt).utf8(rt);

	const char *str = jsString.c_str();
	
	return globalParse->call(rt, String::createFromUtf8(rt, (const unsigned char *)str, strlen(str)));
};

static Value testJsonJSParse(Runtime &rt, TurboModule &turboModule,
							 const Value *args, size_t arg_count) {
	callbackId++;
	
	std::string stdstr = args[0].getString(rt).utf8(rt);
	
	const char *str = stdstr.c_str();
	
	return String::createFromUtf8(rt, (const unsigned char *)str, strlen(str));
};





TurboUtilsSpecJSI::TurboUtilsSpecJSI(std::shared_ptr <CallInvoker> jsInvoker) : TurboModule(
																							"exampleViewModule", jsInvoker) {
																								//here we assign our TurboModule object properties
																								methodMap_["helloWorld"] = MethodMetadata{0, helloWorld};
																								methodMap_["send"] = MethodMetadata{0, send};
																								methodMap_["testJsonParseCPP"] = MethodMetadata{0, testJsonParseCPP};
																								methodMap_["testJsonNativeParse"] = MethodMetadata{0, testJsonNativeParse};
																								methodMap_["testJsonJSParse"] = MethodMetadata{0, testJsonJSParse};
																							}
}
