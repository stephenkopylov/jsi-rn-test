import { findNodeHandle, requireNativeComponent, ViewProps } from "react-native";
import * as React from "react";
import { Ref, useEffect, useImperativeHandle, useMemo, useState } from "react";

export const JsiTestView = requireNativeComponent("JsiTestView");

export interface IJsiTestViewComponentRef {
  foo: () => void;
  bar: () => void;
}

export const JsiTestViewComponent: React.FC<ViewProps> = React.forwardRef(
  (props, ref?: Ref<IJsiTestViewComponentRef | any>) => {
    const viewRef = React.useRef<any>(null);

    const [handle, setHandle] = useState<Number | null>(null);

    useEffect(() => {
      if (viewRef.current) {
        setHandle(findNodeHandle(viewRef.current));
      }
    }, [viewRef, viewRef.current]);

    useImperativeHandle(
      ref,
      () => ({
        foo: () => {

          console.log("handle = ", handle);

          // @ts-ignore
          global.exampleViewModule.doSomethingWithView(handle);
        },
        bar: () => {
          console.log("bar");
          // NativeModules.RNExpertOptionMobilePlot.removeIndicator(handle, index);
        }
      }),
      [handle]
    );
    return <JsiTestView style={{ ...props.style }} ref={viewRef} />;
  }
);
