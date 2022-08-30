#pragma once
#include "../json.h"
#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
//反射机制的原理可以看↓
//https://zhuanlan.zhihu.com/p/502729373


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
#define CLASS(class_name,...)class class_name;//用CLASS创建的类具有反射功能
#define STRUCT(struct_name,...)struct struct_name;
	//#define CLASS(class_name,...) class class_name:public Reflection::object
#endif // __REFLECTION_PARSER__

#define REFLECTION_BODY(class_name) \
    friend class Reflection::TypeFieldReflectionOparator::Type##class_name##Operator; \
    friend class PSerializer;
	// public: virtual std::string getTypeName() override {return #class_name;}

#define REFLECTION_TYPE(class_name) \
    namespace Reflection \
    { \
        namespace TypeFieldReflectionOparator \
        { \
            class Type##class_name##Operator; \
        } \
    };


#define REGISTER_FIELD_TO_MAP(name, value) TypeMetaRegisterinterface::registerToFieldMap(name, value);
#define REGISTER_BASE_CLASS_TO_MAP(name, value) TypeMetaRegisterinterface::registerToClassMap(name, value);
#define REGISTER_ARRAY_TO_MAP(name, value) TypeMetaRegisterinterface::registerToArrayMap(name, value);
#define UNREGISTER_ALL TypeMetaRegisterinterface::unregisterAll();


#define MOVAN_REFLECTION_NEW(name, ...) Reflection::ReflectionPtr(#name, new name(__VA_ARGS__));
#define MOVAN_REFLECTION_DELETE(value) \
    if (value) \
    { \
        delete value.operator->(); \
        value.getPtrReference() = nullptr; \
    }


#define MOVAN_REFLECTION_DEEP_COPY(type, dst_ptr, src_ptr) \
    *static_cast<type*>(dst_ptr) = *static_cast<type*>(src_ptr.getPtr());

#define TypeMetaDef(class_name, ptr) \
    Movan::Reflection::ReflectionInstance(Movan::Reflection::TypeMeta::newMetaFromName(#class_name), (class_name*)ptr)

#define TypeMetaDefPtr(class_name, ptr) \
    new Movan::Reflection::ReflectionInstance(Movan::Reflection::TypeMeta::newMetaFromName(#class_name), \
                                              (class_name*)ptr)

	template<typename T, typename U, typename = void>
	struct is_safely_castable : std::false_type
	{};

	template<typename T, typename U>
	struct is_safely_castable<T, U, std::void_t<decltype(static_cast<U>(std::declval<T>()))>> : std::true_type
	{};

	namespace Reflection
	{
		class TypeMeta;
		class FieldAccessor;
		class ArrayAccessor;
		class ReflectionInstance;
	} // namespace Reflection

	//https://blog.csdn.net/xf_zhen/article/details/52224139
	typedef std::function<void(void*, void*)>      SetFuncion;
	typedef std::function<void* (void*)>            GetFuncion;
	typedef std::function<const char* ()>           GetNameFuncion;
	typedef std::function<void(int, void*, void*)> SetArrayFunc;
	typedef std::function<void* (int, void*)>       GetArrayFunc;
	typedef std::function<int(void*)>              GetSizeFunc;
	typedef std::function<bool()>                  GetBoolFunc;

	typedef std::function<void* (const MJson&)>                          ConstructorWithPJson;
	typedef std::function<MJson(void*)>                                 WritePJsonByName;
	typedef std::function<int(Reflection::ReflectionInstance*&, void*)> GetBaseClassReflectionInstanceListFunc;

	//https://www.cnblogs.com/osbreak/p/9418269.html
	typedef std::tuple<SetFuncion, GetFuncion, GetNameFuncion, GetNameFuncion, GetNameFuncion, GetBoolFunc>
		FieldFunctionTuple;
	typedef std::tuple<GetBaseClassReflectionInstanceListFunc, ConstructorWithPJson, WritePJsonByName>
		ClassFunctionTuple;
	typedef std::tuple<SetArrayFunc, GetArrayFunc, GetSizeFunc, GetNameFuncion, GetNameFuncion> ArrayFunctionTuple;



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

			static TypeMeta newMetaFromName(std::string type_name);//以名称命名元数据

			static bool               newArrayAccessorFromName(std::string array_type_name, ArrayAccessor& accessor);
			static ReflectionInstance newFromNameAndPJson(std::string type_name, const MJson& json_context);
			static MJson              writeByName(std::string type_name, void* instance);

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



		class FieldAccessor
		{
			friend class TypeMeta;

		public:
			FieldAccessor();

			void* get(void* instance);
			void set(void* instance, void* value);


			TypeMeta getOwnerTypeMeta();


			bool getTypeMeta(TypeMeta& field_type);
			const char* getFieldName()const;
			const char* getFieldTypeName();
			const char* getFiedTypeName();
			bool isArrayType();

			FieldAccessor& operator=(const FieldAccessor& dest);
			const char* getArrayTypeName();
			const char* getElementTypeName();
			void set(int index, void* instance, void* element_value);

			void* get(int index, void* instance);
			int getSize(void* instance);

			FieldAccessor& operator=(ArrayAccessor& dest);

		private:
			FieldAccessor(FieldFunctionTuple* functions);
			FieldFunctionTuple* m_functions;
			const char* m_field_name;
			const char* m_field_type_name;

		};


		class ArrayAccessor
		{
			friend class TypeMeta;


		public:
			ArrayAccessor();
			const char* getArrayTypeName();
			const char* getElementTypeName();
			void set(int index, void* instance, void* element_value);

			void* get(int index, void* instance);
			int getSize(void* instance);

			ArrayAccessor& operator=(ArrayAccessor& dest);

		private:
			ArrayAccessor(ArrayFunctionTuple* array_func);

		private:
			ArrayFunctionTuple* m_func;
			const char* m_array_type_name;
			const char* m_element_type_name;

		};



		class ReflectionInstance
		{
		public:
			ReflectionInstance(TypeMeta meta, void* instance) : m_meta(meta), m_instance(instance) {}
			ReflectionInstance() : m_meta(), m_instance(nullptr) {}

			ReflectionInstance& operator=(ReflectionInstance& dest);

			ReflectionInstance& operator=(ReflectionInstance&& dest);

		public:
			TypeMeta m_meta;
			void* m_instance;
		};
		template<typename T>
		class ReflectionPtr
		{
			template<typename U>
			friend class ReflectionPtr;

		public:
			ReflectionPtr(std::string type_name, T* instance) : m_type_name(type_name), m_instance(instance) {}
			ReflectionPtr() : m_type_name(), m_instance(nullptr) {}

			ReflectionPtr(const ReflectionPtr& dest) : m_type_name(dest.m_type_name), m_instance(dest.m_instance) {}

			template<typename U /*, typename = typename std::enable_if<std::is_safely_castable<T*, U*>::value>::type */>
			ReflectionPtr<T>& operator=(const ReflectionPtr<U>& dest)
			{
				if (this == static_cast<void*>(&dest))
				{
					return *this;
				}
				m_type_name = dest.m_type_name;
				m_instance = static_cast<T*>(dest.m_instance);
				return *this;
			}

			template<typename U /*, typename = typename std::enable_if<std::is_safely_castable<T*, U*>::value>::type*/>
			ReflectionPtr<T>& operator=(ReflectionPtr<U>&& dest)
			{
				if (this == static_cast<void*>(&dest))
				{
					return *this;
				}
				m_type_name = dest.m_type_name;
				m_instance = static_cast<T*>(dest.m_instance);
				return *this;
			}

			ReflectionPtr<T>& operator=(const ReflectionPtr<T>& dest)
			{
				if (this == &dest)
				{
					return *this;
				}
				m_type_name = dest.m_type_name;
				m_instance = dest.m_instance;
				return *this;
			}

			ReflectionPtr<T>& operator=(ReflectionPtr<T>&& dest)
			{
				if (this == &dest)
				{
					return *this;
				}
				m_type_name = dest.m_type_name;
				m_instance = dest.m_instance;
				return *this;
			}

			std::string getTypeName() const { return m_type_name; }

			void setTypeName(std::string name) { m_type_name = name; }

			bool operator==(const T* ptr) const { return (m_instance == ptr); }

			bool operator!=(const T* ptr) const { return (m_instance != ptr); }

			bool operator==(const ReflectionPtr<T>& rhs_ptr) const { return (m_instance == rhs_ptr.m_instance); }

			bool operator!=(const ReflectionPtr<T>& rhs_ptr) const { return (m_instance != rhs_ptr.m_instance); }

			template<
				typename T1 /*, typename = typename std::enable_if<std::is_safely_castable<T*, T1*>::value>::type*/>
				explicit operator T1* ()
			{
				return static_cast<T1*>(m_instance);
			}

			template<
				typename T1 /*, typename = typename std::enable_if<std::is_safely_castable<T*, T1*>::value>::type*/>
				operator ReflectionPtr<T1>()
			{
				return ReflectionPtr<T1>(m_type_name, (T1*)(m_instance));
			}

			template<
				typename T1 /*, typename = typename std::enable_if<std::is_safely_castable<T*, T1*>::value>::type*/>
				explicit operator const T1* () const
			{
				return static_cast<T1*>(m_instance);
			}

			template<
				typename T1 /*, typename = typename std::enable_if<std::is_safely_castable<T*, T1*>::value>::type*/>
				operator const ReflectionPtr<T1>() const
			{
				return ReflectionPtr<T1>(m_type_name, (T1*)(m_instance));
			}

			T* operator->() { return m_instance; }

			T* operator->() const { return m_instance; }

			T& operator*() { return *(m_instance); }

			T* getPtr() { return m_instance; }

			T* getPtr() const { return m_instance; }

			const T& operator*() const { return *(static_cast<const T*>(m_instance)); }

			T*& getPtrReference() { return m_instance; }

			operator bool() const { return (m_instance != nullptr); }

		private:
			std::string m_type_name{ "" };
			typedef T   m_type;
			T* m_instance{ nullptr };
		};
	}// namespace Reflection
}// namespace Movan