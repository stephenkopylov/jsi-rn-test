//
//  thread-test.hpp
//  react-native-jsi-test
//
//  Created by Stepan Kopylov on 19/11/2021.
//

#ifndef thread_test_hpp
#define thread_test_hpp

#include <stdio.h>
#include <functional>

class threadTest{
public:
	static void runOnOtherThread(std::function<void()> x);
};
	


#endif /* thread_test_hpp */
