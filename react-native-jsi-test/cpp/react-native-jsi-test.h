#ifndef EXAMPLE_H
#define EXAMPLE_H
#include <jsi/jsi.h>
#include "thread-test.hpp"
#include <ReactCommon/CallInvoker.h>
using namespace facebook::react;
using namespace facebook::jsi;
using namespace std;


namespace example {
  int helloWorld(float a);
  void install(Runtime & jsiRuntime, std::shared_ptr<CallInvoker> callInvoker) ;
}

#endif /* EXAMPLE_H */
