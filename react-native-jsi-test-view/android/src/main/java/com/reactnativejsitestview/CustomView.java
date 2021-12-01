package com.reactnativejsitestview;

import android.content.Context;
import android.util.Log;
import android.view.View;

import com.facebook.react.ReactRootView;

public class CustomView extends View {
  private NativeProxy nativeProxy;

  public CustomView(Context context, NativeProxy cNativeProxy) {
    super(context);
    nativeProxy = cNativeProxy;
  }

  @Override
  public void setId(int id) {
    super.setId(id);
    Log.d("Test", String.valueOf(this.getId()));
    nativeProxy.setId(id);
  }
}
