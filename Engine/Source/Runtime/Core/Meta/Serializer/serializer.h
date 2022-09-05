#pragma once
#include "..\json.h"
#include "..\Reflection\reflection.h"

#include<cassert>

namespace Movan
{
	template<typename...>
	inline constexpr bool always_false = false;

	class MPerializer
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
		static T& read(const MJson& json_context, T& instance)
		{
			if constexpr (std::is_pointer<T>::value)
			{
				return readPointer(json_context, instance);
			}
			else
			{
				static_assert(always_false<T>, "MSerializer::write<T> has not been implemented yet!");
				return PJson();
			}
		}
	};
}