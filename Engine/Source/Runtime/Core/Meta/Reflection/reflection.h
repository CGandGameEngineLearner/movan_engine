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






	namespace Reflection
	{
		class TypeMetaRegisterinterface//元数据注册接口
		{
		public:
			static void registerToClassMap(const char* name, ClassFunctionTuple* value);
			static void registerToFieldMap(const char* name, FieldFunctionTuple* value);
			static void registerToArrayMap(const char* name, ArrayFunctionTuple* value);

			static void unregisterAll();
		};
        class TypeMeta//元数据类型
        {
            friend class FieldAccessor;
            friend class ArrayAccessor;
            friend class TypeMetaRegisterinterface;

        public:
            TypeMeta();

            // static void Register();

            static TypeMeta newMetaFromName(std::string type_name);

            static bool               newArrayAccessorFromName(std::string array_type_name, ArrayAccessor& accessor);
            static ReflectionInstance newFromNameAndPJson(std::string type_name, const PJson& json_context);
            static PJson              writeByName(std::string type_name, void* instance);

            std::string getTypeName();

            int getFieldsList(FieldAccessor*& out_list);

            int getBaseClassReflectionInstanceList(ReflectionInstance*& out_list, void* instance);

            FieldAccessor getFieldByName(const char* name);

            bool isValid() { return m_is_valid; }

            TypeMeta& operator=(const TypeMeta& dest);

        private:
            TypeMeta(std::string type_name);

        private:
            std::vector<FieldAccessor, std::allocator<FieldAccessor>> m_fields;

            std::string m_type_name;

            bool m_is_valid;
        };
	}
}