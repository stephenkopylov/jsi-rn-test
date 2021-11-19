#ifndef EXAMPLE_H
#define EXAMPLE_H
#include <jsi/jsi.h>
#include "thread-test.hpp"
#include <ReactCommon/CallInvoker.h>
#ifdef __ANDROID__
  #include <TurboModule.h>
#else
#include <ReactCommon/TurboModule.h>
#endif

using namespace facebook::react;
using namespace facebook::jsi;
using namespace std;

namespace example {
  int helloWorld(float a);
  void install(Runtime & jsiRuntime, std::shared_ptr<CallInvoker> callInvoker) ;

// This abstract class defines JSI interfaces for the turbo module
class JSI_EXPORT TurboUtilsSpecJSI : public facebook::react::TurboModule {
protected:
	TurboUtilsSpecJSI(std::shared_ptr<facebook::react::CallInvoker> jsInvoker);

public:
	// define our interface methods
	virtual String nativeGreeting(Runtime &rt, const String &name) = 0;
	virtual Value nativeSumSquares(Runtime &rt, double a, double b) = 0;
};

// This is the actual implementation of the module methods
  class UtilsTurboModule : public TurboUtilsSpecJSI {
  public:
	  UtilsTurboModule(std::shared_ptr<CallInvoker> jsInvoker): TurboUtilsSpecJSI(jsInvoker){}

	  String nativeGreeting(Runtime &rt, const String &name) override;
	  Value nativeSumSquares(Runtime &rt, double a, double b) override;
  };

}

#endif /* EXAMPLE_H */
