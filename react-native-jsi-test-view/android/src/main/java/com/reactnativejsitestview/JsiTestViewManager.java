package com.reactnativejsitestview;

import androidx.annotation.NonNull;

import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;

public class JsiTestViewManager extends SimpleViewManager {
  private NativeProxy nativeProxy;

  public JsiTestViewManager(NativeProxy cNativeProxy){
    nativeProxy = cNativeProxy;
  }

  @NonNull
  @Override
  public String getName() {
    return "JsiTestView";
  }

  @NonNull
  @Override
  protected CustomView createViewInstance(@NonNull ThemedReactContext reactContext) {
    return new CustomView(reactContext, nativeProxy);
  }
}
