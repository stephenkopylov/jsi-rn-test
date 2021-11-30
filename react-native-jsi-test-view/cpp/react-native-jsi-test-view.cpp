#include "react-native-jsi-test-view.h"
#include <thread>
#include <map>
#include "JSIObjectToRapidJsonConverter.h"

static std::shared_ptr <CallInvoker> globalCallInvoker;

static Runtime *globaRuntime;

static std::shared_ptr <Function> globalOnMessageCallback;

static std::map <int, std::shared_ptr <Function>> globalCallbacksStore;

namespace exampleView {
void install(Runtime &jsiRuntime, std::shared_ptr <CallInvoker> callInvoker) {
	globalCallInvoker = callInvoker;
	globaRuntime = &jsiRuntime;
	globalOnMessageCallback = NULL;
	globalCallbacksStore = std::map<int, std::shared_ptr <Function>>();
	
	std::shared_ptr <UtilsTurboModule> nativeModule =
	std::make_shared<UtilsTurboModule>(callInvoker);
	
	jsiRuntime.global().setProperty(jsiRuntime,
									PropNameID::forAscii(jsiRuntime, "exampleViewModule"),
									Object::createFromHostObject(jsiRuntime, nativeModule));
}


static Value doSomethingWithView(Runtime &rt, TurboModule &turboModule,
							 const Value *args, size_t arg_count) {
//	double tag = args[0].getNumber();
	
	
	return Value::null();
};


TurboUtilsSpecJSI::TurboUtilsSpecJSI(std::shared_ptr <CallInvoker> jsInvoker) : TurboModule(
																							"exampleViewModule", jsInvoker) {
																								//here we assign our TurboModule object properties
																								methodMap_["doSomethingWithView"] = MethodMetadata{0, doSomethingWithView};
																							}
}
