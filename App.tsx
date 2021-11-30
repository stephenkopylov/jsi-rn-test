import {JsiTestViewComponent} from 'react-native-jsi-test-view/src/';

/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * Generated with the TypeScript template
 * https://github.com/react-native-community/react-native-template-typescript
 *
 * @format
 */

import React, {useState} from 'react';
import {
  SafeAreaView,
  StatusBar,
  StyleSheet,
  Text,
  TouchableWithoutFeedback,
  useColorScheme,
  View,
} from 'react-native';

import {Colors} from 'react-native/Libraries/NewAppScreen';
const sampleJson = {
  test: '123',
  test2: 123,
  test3: {
    testNested: '123',
    nestedArray: ['123', 123, {test: '111'}],
  },
};

const App: React.FC = () => {
  const [result, setResult] = useState<string>('');

  const isDarkMode = useColorScheme() === 'dark';

  const backgroundStyle = {
    backgroundColor: isDarkMode ? Colors.darker : Colors.lighter,
  };

  return (
    <SafeAreaView style={backgroundStyle}>
      <StatusBar barStyle={isDarkMode ? 'light-content' : 'dark-content'} />
      <View>
        <TouchableWithoutFeedback
          onPress={() => {
            // @ts-ignore
            const prev = global.nativePerformanceNow();
            // @ts-ignore
            global.exampleModule.send(() => {
              // @ts-ignore
              setResult(`${global.nativePerformanceNow() - prev}`);
            });
          }}>
          <View style={styles.innerButtonContainer}>
            <Text>{'send'}</Text>
          </View>
        </TouchableWithoutFeedback>
        <TouchableWithoutFeedback
          onPress={() => {
            // @ts-ignore
            const prev = global.nativePerformanceNow();

            let result = null;

            for (let i = 0; i < 10000; i++) {
              // @ts-ignore
              result = global.exampleModule.testJsonParseCPP({
                testtest: i,
                ...sampleJson,
              });
            }

            setResult(
              // @ts-ignore
              `${global.nativePerformanceNow() - prev} ${JSON.stringify(
                result,
              )}`,
            );
          }}>
          <View style={styles.innerButtonContainer}>
            <Text>{'test json parse cpp'}</Text>
          </View>
        </TouchableWithoutFeedback>
        <TouchableWithoutFeedback
          onPress={() => {
            // @ts-ignore
            const prev = global.nativePerformanceNow();

            let result = null;

            for (let i = 0; i < 10000; i++) {
              // @ts-ignore
              result = global.exampleModule.testJsonNativeParse({
                testtest: i,
                ...sampleJson,
              });
            }

            setResult(
              // @ts-ignore
              `${global.nativePerformanceNow() - prev} ${JSON.stringify(
                result,
              )}`,
            );
          }}>
          <View style={styles.innerButtonContainer}>
            <Text>{'test json parse using createFromJsonUtf8'}</Text>
          </View>
        </TouchableWithoutFeedback>
        <TouchableWithoutFeedback
          onPress={() => {
            // @ts-ignore
            const prev = global.nativePerformanceNow();

            let result = null;

            for (let i = 0; i < 10000; i++) {
              result = JSON.parse(
                // @ts-ignore
                global.exampleModule.testJsonJSParse(
                  JSON.stringify({testtest: i, ...sampleJson}),
                ),
              );
            }

            setResult(
              // @ts-ignore
              `${global.nativePerformanceNow() - prev} ${JSON.stringify(
                result,
              )}`,
            );
          }}>
          <View style={styles.innerButtonContainer}>
            <Text>{'test json parse using json parse'}</Text>
          </View>
        </TouchableWithoutFeedback>
        <TouchableWithoutFeedback
          onPress={() => {
            console.log(
              // @ts-ignore
              global.exampleViewModule.testJsonJSParse(
                JSON.stringify(sampleJson),
              ),
            );
          }}>
          <View style={styles.innerButtonContainer}>
            <Text>{'view module test'}</Text>
          </View>
        </TouchableWithoutFeedback>
      </View>
      <JsiTestViewComponent style={{width:10, height:10, backgroundColor:'red'}}/>
      <Text
        style={{
          height: 100,
          backgroundColor: 'white',
          color: 'black',
        }}>{`result: ${result}`}</Text>
    </SafeAreaView>
  );
};

const styles = StyleSheet.create({
  innerButtonContainer: {
    margin: 5,
    height: 100,
    backgroundColor: 'green',
    alignItems: 'center',
    justifyContent: 'center',
  },
  sectionContainer: {
    marginTop: 32,
    paddingHorizontal: 24,
  },
  sectionTitle: {
    fontSize: 24,
    fontWeight: '600',
  },
  sectionDescription: {
    marginTop: 8,
    fontSize: 18,
    fontWeight: '400',
  },
  highlight: {
    fontWeight: '700',
  },
});

export default App;
