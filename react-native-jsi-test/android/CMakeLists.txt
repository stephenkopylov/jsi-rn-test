cmake_minimum_required(VERSION 3.9.0)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 11)

add_library(cpp
            SHARED
            ../cpp/react-native-jsi-test.cpp
            ../../react-native/ReactCommon/jsi/jsi/jsi.cpp
            ./cpp-adapter.cpp
)

include_directories(
        ../../react-native/React
        ../../react-native/React/Base
        ../../react-native/ReactCommon/jsi
        ../cpp
)
