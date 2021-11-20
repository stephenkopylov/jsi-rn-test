#include "react-native-jsi-test.h"
#include <thread>

static std::shared_ptr <CallInvoker> globalCallInvoker;
static Runtime *globaRuntime;

namespace example {
    void install(Runtime &jsiRuntime, std::shared_ptr <CallInvoker> callInvoker) {

        globalCallInvoker = callInvoker;

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


    static Value _helloWorld(Runtime &rt, TurboModule &turboModule,
                             const Value *args, size_t arg_count) {

        //	Function callback = args[0].getObject(rt).getFunction(rt);
        //	const auto callInvoker = dynamic_cast<TurboUtilsSpecJSI *>(&turboModule)->jsInvoker_;

        globaRuntime = &rt;

        auto callback = std::make_shared<Function>(args[0].getObject(rt).getFunction(rt));

        String string = String::createFromUtf8(rt, "helloworld");

        std::thread th{[callback = move(callback), string = move(string), &rt]() {
            LOG("BEFORE SLEEP");
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            LOG("AFTER SLEEP");
            //            if (turboModule.jsInvoker_ != nullptr) {
            LOG("1");
            LOG("2");
            //                    const auto callInvoker = dynamic_cast<TurboUtilsSpecJSI *>(&turboModule)->jsInvoker_;
            LOG("3");
            //
            globalCallInvoker->invokeAsync([callback = move(callback), &string]() {
//
//
//                callback->call(*globaRuntime, Value::null());
                LOG("5");
            });
            //            }
        }

		};

        th.detach();

        return Value::null();
    };

    TurboUtilsSpecJSI::TurboUtilsSpecJSI(std::shared_ptr <CallInvoker> jsInvoker) : TurboModule(
            "exampleModule", jsInvoker) {
        //here we assign our TurboModule object properties
        methodMap_["helloWorld"] = MethodMetadata{0, move(_helloWorld)};
    }

//String UtilsTurboModule::nativeGreeting(Runtime &rt, const String &name) {
//	return String::createFromUtf8(rt, "123123");
//}
//
//Value UtilsTurboModule::nativeSumSquares(Runtime &rt, double a, double b) {
//	return Value::null();
//}

}
