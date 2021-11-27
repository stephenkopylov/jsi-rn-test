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
#include "Logging.h"

using namespace facebook::react;
using namespace facebook::jsi;
using namespace std;

namespace exampleView {
int helloWorld(float a);
void install(Runtime & jsiRuntime, std::shared_ptr<CallInvoker> callInvoker) ;

// This abstract class defines JSI interfaces for the turbo module
class JSI_EXPORT TurboUtilsSpecJSI : public facebook::react::TurboModule {
protected:
	TurboUtilsSpecJSI(std::shared_ptr<facebook::react::CallInvoker> jsInvoker);
};

// This is the actual implementation of the module methods
class UtilsTurboModule : public TurboUtilsSpecJSI {
public:
	UtilsTurboModule(std::shared_ptr<CallInvoker> jsInvoker): TurboUtilsSpecJSI(jsInvoker){}
};

}

#endif /* EXAMPLE_H */
