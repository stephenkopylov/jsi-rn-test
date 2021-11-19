#ifndef EXAMPLE_H
#define EXAMPLE_H
#include <jsi/jsi.h>
#include "thread-test.hpp"
#include <ReactCommon/CallInvoker.h>

using namespace facebook::jsi;
using namespace std;
using namespace facebook::react;

namespace example {
  int helloWorld(float a);
    void install(Runtime & jsiRuntime) ;
  void install(Runtime & jsiRuntime, CallInvoker &callInvoker) ;
}

#endif /* EXAMPLE_H */
