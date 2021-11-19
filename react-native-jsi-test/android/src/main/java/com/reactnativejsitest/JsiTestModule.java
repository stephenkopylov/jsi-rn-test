package com.reactnativejsitest;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.module.annotations.ReactModule;
import com.facebook.react.bridge.CatalystInstanceImpl;

import com.facebook.react.bridge.JavaScriptContextHolder;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.module.annotations.ReactModule;
import com.facebook.react.turbomodule.core.interfaces.CallInvokerHolder;

import android.util.Log;

import java.lang.ref.WeakReference;

@ReactModule(name = JsiTestModule.NAME)
public class JsiTestModule extends ReactContextBaseJavaModule {
  public static final String NAME = "JsiTest";
  private final WeakReference<ReactApplicationContext> mContext;

  public JsiTestModule(ReactApplicationContext reactContext) {
    super(reactContext);
    mContext = new WeakReference<>(reactContext);
  }

  @Override
  @NonNull
  public String getName() {
    return NAME;
  }

  static {
    try {
      // Used to load the 'native-lib' library on application startup.
      System.loadLibrary("cpp");
    } catch (Exception ignored) {
    }
  }

  @ReactMethod
  public void helloWorld(int a, int b, Promise promise) {
//    int ca = nativeHelloWorld(1);
    promise.resolve(a+b);
  }

  //mContext.get().getCatalystInstance().getJSCallInvokerHolder()

  public void installLib(JavaScriptContextHolder reactContext) {
    if (reactContext.get() != 0) {
      this.nativeInstall(
        reactContext.get()
      );
    } else {
      Log.e("SimpleJsiModule", "JSI Runtime is not available in debug mode");
    }

  }

  public static native int nativeHelloWorld(int a);

  private native void nativeInstall(long jsi);
}
