//
//  RNExpertOptionMobileSocketParser.hpp
//  RNExpertOptionMobileSocket
//
//  Created by Stepan Kopylov on 24/11/2021.
//

#ifndef JSIObjectToRapidJsonConverter_hpp
#define JSIObjectToRapidJsonConverter_hpp

#include <stdio.h>
#include <jsi/jsi.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

class JSIObjectToRapidJsonConverter {
public:
	static std::string convert(facebook::jsi::Runtime &rt, facebook::jsi::Object &value){
		facebook::jsi::Array propertyNames = value.getPropertyNames(rt);
		
		size_t size = propertyNames.size(rt);
		
		rapidjson::Document document = JSIObjectToDocument(rt, value);
		
		return nullptr;
	}
private:
	static int* convertJSIValueToRapidJsonObject(
												 facebook::jsi::Runtime &runtime,
												 const facebook::jsi::Value &value)
	{
		//	if (value.isUndefined() || value.isNull()) {
		//		return nil;
		//	}
		//	if (value.isBool()) {
		//		return @(value.getBool());
		//	}
		//	if (value.isNumber()) {
		//		return @(value.getNumber());
		//	}
		//	if (value.isString()) {
		//		return convertJSIStringToNSString(runtime, value.getString(runtime));
		//	}
		//	if (value.isObject()) {
		//		facebook::jsi::Object o = value.getObject(runtime);
		//		if (o.isArray(runtime)) {
		//			return convertJSIArrayToNSArray(runtime, o.getArray(runtime));
		//		}
		//		return JSIObjectToDocument(runtime, o);
		//	}
		
		throw std::runtime_error("Unsupported jsi::jsi::Value kind");
	}
	
	static rapidjson::Document JSIObjectToDocument(facebook::jsi::Runtime &rt, facebook::jsi::Object &value){
		facebook::jsi::Array propertyNames = value.getPropertyNames(rt);
		
		size_t size = propertyNames.size(rt);
		
		rapidjson::Document document;
		auto& allocator = document.GetAllocator();
		
		document.SetObject();
		
		char const *keyString = "keyStr";
		char const *valueString = "valueStr";
		
		rapidjson::Value key;
		key.SetString(keyString, strlen(keyString));
		
		rapidjson::Value v;
		v.SetBool(false);
//		v.SetString(valueString, strlen(valueString));
		
		document.AddMember(key, v, allocator);
		
		rapidjson::StringBuffer buffer;
		buffer.Clear();
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);
		
		std::string str =  buffer.GetString();
		
		for (size_t i = 0; i < size; i++) {
			facebook::jsi::String name = propertyNames.getValueAtIndex(rt, i).getString(rt);
			
			int* v = convertJSIValueToRapidJsonObject(rt, value.getProperty(rt, name));
			
			if (v) {
			}
		}
		
		return document;
	}
};

#endif /* RNExpertOptionMobileSocketParser_hpp */
