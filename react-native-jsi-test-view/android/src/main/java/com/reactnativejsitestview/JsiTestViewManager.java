package com.reactnativejsitestview;

import android.view.View;

import androidx.annotation.NonNull;

import com.facebook.react.uimanager.SimpleViewManager;
import com.facebook.react.uimanager.ThemedReactContext;

public class JsiTestViewManager extends SimpleViewManager {
  @NonNull
  @Override
  public String getName() {
    return "JsiTestView";
  }

  @NonNull
  @Override
  protected View createViewInstance(@NonNull ThemedReactContext reactContext) {
    return new View(reactContext);
  }
}
