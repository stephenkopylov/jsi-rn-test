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
      return findNodeHandle(viewRef.current);
    }, [viewRef.current]);

    useImperativeHandle(
      ref,
      () => ({
        foo: () => {
          console.log('foo');
          // const i = cloneIndicatorFields(indicator);
          // NativeModules.RNExpertOptionMobilePlot.addIndicator(handle, i);
        },
        bar: () => {
          console.log('bar');
          // NativeModules.RNExpertOptionMobilePlot.removeIndicator(handle, index);
        }
      }),
      [handle]
    );
    return <JsiTestView {...props} ref={viewRef}></JsiTestView>;
  }
);
