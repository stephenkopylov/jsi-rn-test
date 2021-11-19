//
//  thread-test.cpp
//  react-native-jsi-test
//
//  Created by Stepan Kopylov on 19/11/2021.
//

#include "thread-test.hpp"
#include <thread>
#include <chrono>

void threadTest::runOnOtherThread(std::function<void()> x){
	std::thread th { [=](){
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		x();
	}};

	th.join();
}
