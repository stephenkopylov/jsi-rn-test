package com.reactnativejsitestview;

import android.content.Context;
import android.view.TextureView;
import android.view.View;
import android.view.ViewGroup;

public class CustomView extends ViewGroup {
  private final NativeProxy nativeProxy;
  private final TextureView textureView;

  public CustomView(Context context, NativeProxy cNativeProxy) {
    super(context);
    nativeProxy = cNativeProxy;

    textureView = new TextureView(context);
    textureView.setOpaque(false);
    this.addView(textureView);

  }

  @Override
  protected void onLayout(boolean changed, int l, int t, int r, int b) {
    textureView.layout(l,t,r,b);
  }

  @Override
  public void setId(int id) {
    super.setId(id);
    nativeProxy.setId(id);
  }
}
