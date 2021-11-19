#ifndef EXAMPLE_H
#define EXAMPLE_H
#include <jsi/jsi.h>
#include "thread-test.hpp"
#ifndef __ANDROID__
#include <ReactCommon/CallInvoker.h>
using namespace facebook::react;
#endif
using namespace facebook::jsi;
using namespace std;


namespace example {
  int helloWorld(float a);
  void install(Runtime & jsiRuntime) ;
#ifndef __ANDROID__
  void install(Runtime & jsiRuntime, CallInvoker &callInvoker) ;
#endif
}

#endif /* EXAMPLE_H */
