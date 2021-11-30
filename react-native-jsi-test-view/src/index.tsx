import { requireNativeComponent, ViewProps, findNodeHandle } from "react-native";
import * as React from "react";
import { Ref, useImperativeHandle, useMemo } from "react";

export const JsiTestView = requireNativeComponent("JsiTestView");

export interface IJsiTestViewComponentRef {
  foo: () => void;
  bar: () => void;
}

export const JsiTestViewComponent: React.FC<ViewProps> = React.forwardRef(
  (props, ref?: Ref<IJsiTestViewComponentRef | any>) => {
    const viewRef = React.useRef<any>(null);

    const handle = useMemo(() => {
      const cHandle = findNodeHandle(viewRef.current);
      console.log("finding handle = ", cHandle, ' viewRef = ', viewRef.current);
      return cHandle;
    }, [viewRef.current]);

    useImperativeHandle(
      ref,
      () => ({
        foo: () => {

          console.log("handle = ", handle);

          // @ts-ignore
          global.exampleViewModule.doSomethingWithView(handle);
          // const i = cloneIndicatorFields(indicator);
          // NativeModules.RNExpertOptionMobilePlot.addIndicator(handle, i);
        },
        bar: () => {
          console.log("bar");
          // NativeModules.RNExpertOptionMobilePlot.removeIndicator(handle, index);
        }
      }),
      [handle]
    );
    return <JsiTestView style={{...props.style}} ref={viewRef}></JsiTestView>;
  }
);
