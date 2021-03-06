#include <jni.h>
#include <CallInvokerHolder.h>
#include <fbjni/fbjni.h>
#include <jsi/jsi.h>
#include "react-native-jsi-test.h"

#define TAG "CPPMODULE"

#ifdef __ANDROID__
#include <android/log.h>

#define LOG(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)

#endif

using namespace facebook;

struct NativeProxy : jni::JavaClass<NativeProxy> {
    static constexpr auto kJavaDescriptor = "Lcom/reactnativejsitest/NativeProxy;";

    static void registerNatives() {
        javaClassStatic()->registerNatives({
                                                   makeNativeMethod("installNativeJsi",
                                                                    NativeProxy::installNativeJsi)
                                           });
    }

private:
    static void installNativeJsi(jni::alias_ref<jni::JObject> thiz,
                                 jlong jsiRuntimePtr,
                                 jni::alias_ref<react::CallInvokerHolder::javaobject> jsCallInvokerHolder) {

        auto jsiRuntime = reinterpret_cast<jsi::Runtime *>(jsiRuntimePtr);
        auto jsCallInvoker = jsCallInvokerHolder->cthis()->getCallInvoker();

        LOG("installNativeJsi");

        example::install(*jsiRuntime, jsCallInvoker);
    }
};

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *) {
    LOG("JNI ON LOAD");

    return jni::initialize(vm, [] {
        LOG("installNativeJsi");

        NativeProxy::registerNatives();
    });
}
