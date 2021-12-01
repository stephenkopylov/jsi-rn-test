package com.reactnativejsitestview;

import android.content.Context;
import android.util.Log;
import android.view.View;

import com.facebook.react.ReactRootView;

public class CustomView extends View {
  public CustomView(Context context) {
    super(context);
  }

  @Override
  public void setId(int id) {
    super.setId(id);
  }
}
