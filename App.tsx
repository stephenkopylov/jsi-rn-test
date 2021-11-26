/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * Generated with the TypeScript template
 * https://github.com/react-native-community/react-native-template-typescript
 *
 * @format
 */

const LARGE_STRING = '123123';

import React, {useCallback, useEffect, useMemo, useState} from 'react';
import {
  SafeAreaView,
  ScrollView,
  StatusBar,
  StyleSheet,
  Text,
  TouchableOpacity,
  useColorScheme,
  View,
} from 'react-native';

import {helloWorld} from './node_modules/react-native-jsi-test/src';

import {
  Colors,
  DebugInstructions,
  Header,
  LearnMoreLinks,
  ReloadInstructions,
} from 'react-native/Libraries/NewAppScreen';

const Section: React.FC<{
  title: string;
}> = ({children, title}) => {
  const isDarkMode = useColorScheme() === 'dark';
  return (
    <View style={styles.sectionContainer}>
      <Text
        style={[
          styles.sectionTitle,
          {
            color: isDarkMode ? Colors.white : Colors.black,
          },
        ]}>
        {title}
      </Text>
      <Text
        style={[
          styles.sectionDescription,
          {
            color: isDarkMode ? Colors.light : Colors.dark,
          },
        ]}>
        {children}
      </Text>
    </View>
  );
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
        <TouchableOpacity
          onPress={() => {
            // @ts-ignore
            const prev = global.nativePerformanceNow();
            // @ts-ignore
            global.exampleModule.send(() => {
              // @ts-ignore
              setResult(`${global.nativePerformanceNow() - prev}`);
            });
          }}>
          <View
            style={{
              margin: 5,
              height: 100,
              backgroundColor: 'green',
              alignItems: 'center',
              justifyContent: 'center',
            }}>
            <Text>{'send'}</Text>
          </View>
        </TouchableOpacity>
        <TouchableOpacity
          onPress={() => {
            // @ts-ignore
            const result = global.exampleModule.testJson({
              test: '123',
              test2: 123,
              test3: {
                testNested: '123',
                nestedArray: ['123', 123, {test: '111'}],
              },
            });
            console.log('result = ', result);
          }}>
          <View
            style={{
              margin: 5,
              height: 100,
              backgroundColor: 'green',
              alignItems: 'center',
              justifyContent: 'center',
            }}>
            <Text>{'test json'}</Text>
          </View>
        </TouchableOpacity>
      </View>
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
