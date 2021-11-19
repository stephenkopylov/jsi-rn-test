#import "JsiTest.h"
#import <React/RCTBridge+Private.h>
#import <React/RCTUtils.h>
#import <ReactCommon/CallInvoker.h>
//#import <React/CallInvoker.h>
#import "react-native-jsi-test.h"
#import "RCTTurboModule.h"
#import <ReactCommon/RCTTurboModule.h>

@implementation JsiTest

@synthesize bridge = _bridge;

RCT_EXPORT_MODULE()

// Example method for C++
// See the implementation of the example module in the `cpp` folder
RCT_EXPORT_METHOD(helloWorld:(nonnull NSNumber*)x
				  andY:(nonnull NSNumber*)y
                  withResolver:(RCTPromiseResolveBlock)resolve
                  withReject:(RCTPromiseRejectBlock)reject)
{
    NSNumber *result = @(x.intValue + y.intValue);

	resolve(result);
}

+(BOOL)requiresMainQueueSetup{
    return YES;
}

- (void)setBridge:(RCTBridge *)bridge {
    _bridge = bridge;
    [self installLibrary];
}

- (void)installLibrary {
    RCTCxxBridge *cxxBridge = (RCTCxxBridge *)self.bridge;

    if (cxxBridge.runtime) {
		example::install(*(facebook::jsi::Runtime *)cxxBridge.runtime, cxxBridge.jsCallInvoker);
    }
}

@end
