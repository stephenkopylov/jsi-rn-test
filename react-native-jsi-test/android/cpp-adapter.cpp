#include <jni.h>
#include "react-native-jsi-test.h"

extern "C"
JNIEXPORT jint JNICALL
Java_com_reactnativejsitest_JsiTestModule_nativeHelloWorld(JNIEnv *env, jclass type, jint a) {
    return example::helloWorld(a);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_reactnativejsitest_JsiTestModule_nativeInstall(JNIEnv *env, jobject thiz, jlong jsi) {
    auto runtime = reinterpret_cast<facebook::jsi::Runtime *>(jsi);


    if (runtime) {
        example::install(*runtime);
    }
}
