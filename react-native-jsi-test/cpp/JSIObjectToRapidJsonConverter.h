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
#include <rapidjson/allocators.h>

class JSIObjectToRapidJsonConverter {
public:
	static std::string convert(facebook::jsi::Runtime &rt, facebook::jsi::Object &value){
		rapidjson::Document document;
		rapidjson::Value jsonValue = JSIObjectToDocument(rt, value, document.GetAllocator());
		
		rapidjson::Document d;
		d.CopyFrom(jsonValue, document.GetAllocator());
		
		rapidjson::StringBuffer buffer;
		buffer.Clear();
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		d.Accept(writer);
		
		return buffer.GetString();
	}
private:
	static rapidjson::Value JSIObjectToDocument(
												   facebook::jsi::Runtime &rt,
												   facebook::jsi::Object &value,
												   rapidjson::MemoryPoolAllocator<> &allocator){
		facebook::jsi::Array propertyNames = value.getPropertyNames(rt);
		
		size_t size = propertyNames.size(rt);
		
		rapidjson::Value jsonValue;
		jsonValue.SetObject();
		
		for (size_t i = 0; i < size; i++) {
			facebook::jsi::String key = propertyNames.getValueAtIndex(rt, i).getString(rt);
			
			char const *keyString = key.utf8(rt).c_str();
			
			rapidjson::Value keyValue;
			keyValue.SetString(keyString, (int)strlen(keyString), allocator);
			
			rapidjson::Value valueValue = convertJSIValueToRapidJsonObject(rt, value.getProperty(rt, key), allocator);
			
			if (!valueValue.IsNull()) {
				jsonValue.AddMember(keyValue, valueValue, allocator);
			}
		}
		
		return jsonValue;
	}
	
	static rapidjson::Value convertJSIValueToRapidJsonObject(
															 facebook::jsi::Runtime &rt,
															 const facebook::jsi::Value &value,
															 rapidjson::MemoryPoolAllocator<> &allocator
															 )
	{
		rapidjson::Value v;
		
		if (value.isUndefined() || value.isNull()) {
			v.SetNull();
		}
		if (value.isBool()) {
			v.SetBool(value.getBool());
		}
		if (value.isNumber()) {
			v.SetDouble(value.getNumber());
		}
		if (value.isString()) {
			char const *stringValue = value.getString(rt).utf8(rt).c_str();
			v.SetString(stringValue, (int)strlen(stringValue), allocator);
		}
		if (value.isObject()) {
			facebook::jsi::Object o = value.getObject(rt);
//			if (o.isArray(runtime)) {
//				return convertJSIArrayToNSArray(runtime, o.getArray(runtime));
//			}
			v = JSIObjectToDocument(rt, o, allocator);
		}
		
		return v;
		
		throw std::runtime_error("Unsupported jsi::jsi::Value kind");
	}
	

};

#endif /* RNExpertOptionMobileSocketParser_hpp */
