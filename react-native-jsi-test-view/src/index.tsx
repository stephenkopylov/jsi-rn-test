import { requireNativeComponent, ViewProps } from "react-native";
import * as React from 'react';

export const JsiTestView = requireNativeComponent("JsiTestView");

export const JsiTestViewComponent: React.FC<ViewProps> = (props) => {

  return (<JsiTestView {...props}></JsiTestView>);
};
