package com.reactnativejsitestview;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.module.annotations.ReactModule;

@ReactModule(name = JsiTestViewModule.NAME)
public class JsiTestViewModule extends ReactContextBaseJavaModule {
  public static final String NAME = "JsiTestView";

  NativeProxy nativeProxy = new NativeProxy();

  public JsiTestViewModule(ReactApplicationContext reactContext) {
    super(reactContext);
  }

  @Override
  public void initialize() {
    super.initialize();
    nativeProxy.installJsi(this.getReactApplicationContext());
  }

  @Override
  @NonNull
  public String getName() {
    return NAME;
  }

  static {
    try {
      // Used to load the 'native-lib' library on application startup.
      System.loadLibrary("cpp-view");
    } catch (Exception ignored) {
    }
  }

  @ReactMethod
  public void helloWorld(int a, int b, Promise promise) {
//    int ca = nativeHelloWorld(1);
    promise.resolve(a+b);
  }
}
