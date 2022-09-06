#pragma once
#include "..\json.h"
#include "..\Reflection\reflection.h"

#include<cassert>

namespace Movan
{
	template<typename...>
	inline constexpr bool always_false = false;

	class MSerializer
	{
	public:
		template<typename T>
		static MJson writePointer(T* instance)
		{
			return MJson::object{{"$typeName",MJson{"*"}},{"$context",MSerializer::write(*instance)}};
		}

		template<typename T>
		static T*& readPointer(const MJson& json_context, T*& instance)
		{
			assert(instance == nullptr);
			std::string type_name = json_context["$typeName"].string_value();
			assert(!type_name.empty());
			if ('*' == type_name[0])
			{
				instance = new T;
				read(json_context["$context"], *instance);
			}
			else
			{
				instance=static_cast<T*>(Reflection::TypeMeta::newFromNameAndPJson(type_name,json_context["$context"]).m_instance)
			}
			return instance;
		}

		template<typename T>
		static MJson write(const Reflection::ReflectionPtr<T>& instance)
		{
			T* instance_ptr = static_cast<T*>(instance.operator->());
			std::string type_name = instance.getTypeName();

			return MJson::object{ {"$typeName",MJson(type_name)},{"$context",Reflection::TypeMeta::writeByName(type_name,instance_ptr)} };
		}

		template<typename T>
		static T*& read(const MJson& json_context, Reflection::ReflectionPtr<T>& instance)
		{
			std::string type_name = json_context["$typeName"].string_value();
			instance.setTypeName(type_name);
			return readPointer(json_context, instance.getPtrReference());
		}

		template<typename T>
		static MJson write(const T& instance)
		{

			if constexpr (std::is_pointer<T>::value)
			{
				return writePointer((T)instance);
			}
			else
			{
				static_assert(always_false<T>, "PSerializer::write<T> has not been implemented yet!");
				return MJson();
			}
		}

		template<typename T>
		static T& read(const MJson& json_context, T& instance)
		{
			if constexpr (std::is_pointer<T>::value)
			{
				return readPointer(json_context, instance);
			}
			else
			{
				static_assert(always_false<T>, "MSerializer::write<T> has not been implemented yet!");
				return instance;
			}
		}
	};


	//基本类型的实现 implementation of base types

	//char
	template<>
	MJson MSerializer::write(const char& instance);
	template<>
	char& MSerializer::read(const MJson& json_context, char& instance);

	//int
	template<>
	MJson MSerializer::write(const int& instance);
	template<>
	int& MSerializer::read(const MJson& json_context, int& instance);

	//unsigned int
	template<>
	MJson MSerializer::write(const unsigned int& instance);
	template<>
	unsigned int& MSerializer::read(const MJson& json_context, unsigned int& instance);
	
	//float
	template<>
	MJson MSerializer::write(const float& instance);
	template<>
	float& MSerializer::read(const MJson& json_context, float& instance);;

	//double
	template<>
	MJson MSerializer::write(const double& instance);
	template<>
	double& MSerializer::read(const MJson& json, double& instance);

	//bool
	template<>
	MJson MSerializer::write(const bool& instance);
	template<>
	bool& MSerializer::read(const MJson& json_context, bool& instance);

	//string
	template<>
	std::string& MSerializer::write(const std::string& instance);
	template<>
	std::string& MSerializer::read(const MJson& json_context, std::string& instance);
}//namespace Movan