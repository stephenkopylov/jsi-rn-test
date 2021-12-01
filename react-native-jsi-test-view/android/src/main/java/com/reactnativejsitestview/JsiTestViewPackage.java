package com.reactnativejsitestview;

import androidx.annotation.NonNull;
import androidx.lifecycle.MutableLiveData;

import com.facebook.react.ReactPackage;
import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.uimanager.ViewManager;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class JsiTestViewPackage implements ReactPackage {
    private JsiTestViewModule module;

    @NonNull
    @Override
    public List<NativeModule> createNativeModules(@NonNull ReactApplicationContext reactContext) {
        module = new JsiTestViewModule(reactContext);

        List<NativeModule> modules = new ArrayList<>();
        modules.add(module);
        return modules;
    }

    @NonNull
    @Override
    public List<ViewManager> createViewManagers(@NonNull ReactApplicationContext reactContext) {
      return Arrays.<ViewManager>asList(
        new JsiTestViewManager(module.nativeProxy)
      );
    }
}
