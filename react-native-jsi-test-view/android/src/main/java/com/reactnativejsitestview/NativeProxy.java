package com.reactnativejsitestview;

import android.util.Log;

import com.facebook.react.bridge.ReactContext;
import com.facebook.react.turbomodule.core.CallInvokerHolderImpl;

public class NativeProxy {

  /*** jsi stuff ***/          //these could be static as well
  private native void installNativeJsiView(long jsContextNativePointer, CallInvokerHolderImpl jsCallInvokerHolder);

  private native void setNativeId(int id);

  public void installJsi(ReactContext context) {
    Log.d("reactnativejsitestview", "Installing native...");
    CallInvokerHolderImpl holder = (CallInvokerHolderImpl) context.getCatalystInstance().getJSCallInvokerHolder();
    long contextPointer = context.getJavaScriptContextHolder().get();
    installNativeJsiView(contextPointer, holder);

    Log.d("reactnativejsitestview", "success ...");
  }

  public void setId(int id) {
    setNativeId(id);
  }
}
