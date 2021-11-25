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
	static rapidjson::Document convert(facebook::jsi::Runtime &rt, facebook::jsi::Object &value){
		rapidjson::Document document;
		rapidjson::Value jsonValue = JSIObjectToDocument(rt, value, document.GetAllocator());
		
		rapidjson::Document finalDocument;
		finalDocument.CopyFrom(jsonValue, document.GetAllocator());
		
		return finalDocument;
	}
	
	static std::string convertToString(facebook::jsi::Runtime &rt, facebook::jsi::Object &value){
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
			
			std::string string = key.utf8(rt);
			char const *keyString = string.c_str();
			
			rapidjson::Value keyValue;
			keyValue.SetString(keyString, (int)strlen(keyString), allocator);
			
			rapidjson::Value valueValue = convertJSIValueToRapidJsonObject(rt, value.getProperty(rt, key), allocator);
			
			if (!valueValue.IsNull()) {
				jsonValue.AddMember(keyValue, valueValue, allocator);
			}
		}
		
		return jsonValue;
	}
	
	static rapidjson::Value convertJSIArrayToRapidJson(
													   facebook::jsi::Runtime &rt,
													   const facebook::jsi::Array &value,
													   rapidjson::MemoryPoolAllocator<> &allocator)
	{
		size_t size = value.size(rt);
		rapidjson::Value v;
		v.SetArray();
		
		for (size_t i = 0; i < size; i++) {
			rapidjson::Value valueValue =  convertJSIValueToRapidJsonObject(rt, value.getValueAtIndex(rt, i), allocator);
			if (!valueValue.IsNull()) {
				v.PushBack(valueValue, allocator);
			}
		}
		return v;
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
		else if (value.isBool()) {
			v.SetBool(value.getBool());
		}
		else if (value.isNumber()) {
			v.SetDouble(value.getNumber());
		}
		else if (value.isString()) {
			std::string string = value.getString(rt).utf8(rt);
			char const *stringValue = string.c_str();
			v.SetString(stringValue, (int)strlen(stringValue), allocator);
		}
		else if (value.isObject()) {
			facebook::jsi::Object o = value.getObject(rt);
			if (o.isArray(rt)) {
				v = convertJSIArrayToRapidJson(rt, o.getArray(rt), allocator);
			}else{
				v = JSIObjectToDocument(rt, o, allocator);
			}
		}else{
			throw std::runtime_error("Unsupported jsi::jsi::Value kind");
		}
		
		return v;
	}
};

#endif /* RNExpertOptionMobileSocketParser_hpp */
