import { requireNativeComponent, View } from "react-native";
import * as React from 'react';

export const JsiTestView = requireNativeComponent("JsiTestView");

export const JsiTestViewComponent: React.FC<any> = () => {

  return <View></View>
};
