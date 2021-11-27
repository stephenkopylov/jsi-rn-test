cmake_minimum_required(VERSION 3.9.0)

set(CMAKE_VERBOSE_MAKEFILE ON)
#important
set(CMAKE_CXX_STANDARD 14)

set(build_DIR ${CMAKE_SOURCE_DIR}/build)
set(PACKAGE_NAME "cpp-view")  # the name for our library

include_directories(
        ../cpp
        ../thirdParty
        ../../react-native/React
        ../../react-native/React/Base
        ../../react-native/ReactCommon
        ../../react-native/ReactCommon/react/nativemodule/core/ReactCommon
        ../../react-native/ReactCommon/jsi
        ../../react-native/ReactCommon/callinvoker
        ../../react-native/ReactAndroid/src/main/java/com/facebook/react/turbomodule/core/jni/ReactCommon
        ../../react-native/ReactCommon/turbomodule/core
        ../../react-native/ReactCommon/turbomodule
        ../../react-native/React
        ../../react-native/React/Base
        ../../react-native/ReactCommon/jsi
)

find_package(fbjni REQUIRED CONFIG)

add_library(
        ${PACKAGE_NAME}
        SHARED
        ../../react-native/ReactCommon/jsi/jsi/jsi.cpp
        ../../react-native/ReactAndroid/src/main/java/com/facebook/react/turbomodule/core/jni/ReactCommon/CallInvokerHolder.cpp
        ../../react-native/ReactCommon/react/nativemodule/core/ReactCommon/TurboModule.cpp
        ../cpp/react-native-jsi-test-view.cpp
        ./cpp-adapter.cpp
)

target_link_libraries(${PACKAGE_NAME} fbjni::fbjni android log)

add_library(
        turbomodulejsijni
        # Sets the library as a shared library.
        SHARED
        # an empty cpp file
        ../cpp/empty.cpp
)
