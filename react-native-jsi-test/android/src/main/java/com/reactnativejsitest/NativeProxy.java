package com.reactnativejsitest;

import android.util.Log;

import com.facebook.react.bridge.ReactContext;
import com.facebook.react.turbomodule.core.CallInvokerHolderImpl;

public class NativeProxy {

  /*** jsi stuff ***/          //these could be static as well
  private native void installNativeJsi(long jsContextNativePointer, CallInvokerHolderImpl jsCallInvokerHolder);

  public void installJsi(ReactContext context) {
    Log.d("reactnativejsitest", "Installing native...");
    CallInvokerHolderImpl holder = (CallInvokerHolderImpl)context.getCatalystInstance().getJSCallInvokerHolder();
    long contextPointer = context.getJavaScriptContextHolder().get();
    installNativeJsi(contextPointer, holder);

    Log.d("reactnativejsitest", "success ...");
  }
}
