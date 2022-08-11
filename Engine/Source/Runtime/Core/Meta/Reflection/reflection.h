#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Movan
{
#if defined(__REFLECTION_PARSER__)//如果预设了反射解析器
#define META(...) __attribute__((annotate(#__VA_ARGS__)))
#define CLASS(class_name, ...) class __attribute__((annotate(#__VA_ARGS__))) class_name
#define STRUCT(struct_name, ...) struct __attribute__((annotate(#__VA_ARGS__))) struct_name
	//#define CLASS(class_name,...) class __attribute__((annotate(#__VA_ARGS__))) class_name:public Reflection::object
#else
	//变长参数
#define META(...)
#define CLASS(class_name,...)class class_name;
#define STRUCT(struct_name,...)struct struct_name;
	//#define CLASS(class_name,...) class class_name:public Reflection::object
#endif // __REFLECTION_PARSER__

#define REFLECTION_BODY(class_name) \
    friend class Reflection::TypeFieldReflectionOparator::Type##class_name##Operator; \
    friend class PSerializer;
	// public: virtual std::string getTypeName() override {return #class_name;}
}