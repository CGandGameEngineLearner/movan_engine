//
// Created by lifesize
// Email Address: lifesize1@qq.com
//
#include "reflection.h"
#include <cstring>
#include <map>

namespace Movan
{
    namespace Reflection
    {
        const char* k_unknown_type = "UnknownType";
        const char* k_unknown      = "Unknown";

        static std::map<std::string, ClassFunctionTuple*>       _class_map;
        static std::multimap<std::string, FieldFunctionTuple*>  _field_map;
        static std::multimap<std::string, MethodFunctionTuple*> _method_map;
        static std::map<std::string, ArrayFunctionTuple*>       _array_map;

        void TypeMetaRegisterinterface::registerToFieldMap(const char* name, FieldFunctionTuple* value)
        {
            _field_map.insert(std::make_pair(name, value));
        }
        void TypeMetaRegisterinterface::registerToMethodMap(const char* name, MethodFunctionTuple* value)
        {
            _method_map.insert(std::make_pair(name, value));
        }
        void TypeMetaRegisterinterface::registerToArrayMap(const char* name, ArrayFunctionTuple* value)
        {
            if (_array_map.find(name) == _array_map.end())
            {
                _array_map.insert(std::make_pair(name, value));
            }
            else
            {
                delete value;
            }
        }

        void TypeMetaRegisterinterface::registerToClassMap(const char* name, ClassFunctionTuple* value)
        {
            if (_class_map.find(name) == _class_map.end())
            {
                _class_map.insert(std::make_pair(name, value));
            }
            else
            {
                delete value;
            }
        }

        void TypeMetaRegisterinterface::unregisterAll()
        {
            for (const auto& itr : _field_map)
            {
                delete itr.second;
            }
            _field_map.clear();
            for (const auto& itr : _class_map)
            {
                delete itr.second;
            }
            _class_map.clear();
            for (const auto& itr : _array_map)
            {
                delete itr.second;
            }
            _array_map.clear();
        }

        TypeMeta::TypeMeta(std::string type_name) : _type_name(type_name)
        {
            _is_valid = false;
            _fields.clear();
            _methods.clear();

            auto fileds_iter = _field_map.equal_range(type_name);
            while (fileds_iter.first != fileds_iter.second)
            {
                FieldAccessor f_field(fileds_iter.first->second);
                _fields.emplace_back(f_field);
                _is_valid = true;

                ++fileds_iter.first;
            }

            auto methods_iter = _method_map.equal_range(type_name);
            while (methods_iter.first != methods_iter.second)
            {
                MethodAccessor f_method(methods_iter.first->second);
                _methods.emplace_back(f_method);
                _is_valid = true;

                ++methods_iter.first;
            }
        }

        TypeMeta::TypeMeta() : _type_name(k_unknown_type), _is_valid(false) { _fields.clear(); _methods.clear(); }

        TypeMeta TypeMeta::newMetaFromName(std::string type_name)
        {
            TypeMeta f_type(type_name);
            return f_type;
        }

        bool TypeMeta::newArrayAccessorFromName(std::string array_type_name, ArrayAccessor& accessor)
        {
            auto iter = _array_map.find(array_type_name);

            if (iter != _array_map.end())
            {
                ArrayAccessor new_accessor(iter->second);
                accessor = new_accessor;
                return true;
            }

            return false;
        }

        ReflectionInstance TypeMeta::newFromNameAndJson(std::string type_name, const Json& json_context)
        {
            auto iter = _class_map.find(type_name);

            if (iter != _class_map.end())
            {
                return ReflectionInstance(TypeMeta(type_name), (std::get<1>(*iter->second)(json_context)));
            }
            return ReflectionInstance();
        }

        Json TypeMeta::writeByName(std::string type_name, void* instance)
        {
            auto iter = _class_map.find(type_name);

            if (iter != _class_map.end())
            {
                return std::get<2>(*iter->second)(instance);
            }
            return Json();
        }

        std::string TypeMeta::getTypeName() { return _type_name; }

        int TypeMeta::getFieldsList(FieldAccessor*& out_list)
        {
            int count = _fields.size();
            out_list  = new FieldAccessor[count];
            for (int i = 0; i < count; ++i)
            {
                out_list[i] = _fields[i];
            }
            return count;
        }

        int TypeMeta::getMethodsList(MethodAccessor*& out_list)
        {
            int count = _methods.size();
            out_list  = new MethodAccessor[count];
            for (int i = 0; i < count; ++i)
            {
                out_list[i] = _methods[i];
            }
            return count;
        }

        int TypeMeta::getBaseClassReflectionInstanceList(ReflectionInstance*& out_list, void* instance)
        {
            auto iter = _class_map.find(_type_name);

            if (iter != _class_map.end())
            {
                return (std::get<0>(*iter->second))(out_list, instance);
            }

            return 0;
        }

        FieldAccessor TypeMeta::getFieldByName(const char* name)
        {
            const auto it = std::find_if(_fields.begin(), _fields.end(), [&](const auto& i) {
                return std::strcmp(i.getFieldName(), name) == 0;
            });
            if (it != _fields.end())
                return *it;
            return FieldAccessor(nullptr);
        }

        MethodAccessor TypeMeta::getMethodByName(const char* name)
        {
            const auto it = std::find_if(_methods.begin(), _methods.end(), [&](const auto& i) {
                return std::strcmp(i.getMethodName(), name) == 0;
            });
            if (it != _methods.end())
                return *it;
            return MethodAccessor(nullptr);
        }

        TypeMeta& TypeMeta::operator=(const TypeMeta& dest)
        {
            if (this == &dest)
            {
                return *this;
            }
            _fields.clear();
            _fields = dest._fields;


            _methods.clear();
            _methods = dest._methods;

            _type_name = dest._type_name;
            _is_valid  = dest._is_valid;

            return *this;
        }
        FieldAccessor::FieldAccessor()
        {
            _field_type_name = k_unknown_type;
            _field_name      = k_unknown;
            _functions       = nullptr;
        }

        FieldAccessor::FieldAccessor(FieldFunctionTuple* functions) : _functions(functions)
        {
            _field_type_name = k_unknown_type;
            _field_name      = k_unknown;
            if (_functions == nullptr)
            {
                return;
            }

            _field_type_name = (std::get<4>(*_functions))();
            _field_name      = (std::get<3>(*_functions))();
        }

        void* FieldAccessor::get(void* instance)
        {
            // todo: should check validation
            return static_cast<void*>((std::get<1>(*_functions))(instance));
        }

        void FieldAccessor::set(void* instance, void* value)
        {
            // todo: should check validation
            (std::get<0>(*_functions))(instance, value);
        }

        TypeMeta FieldAccessor::getOwnerTypeMeta()
        {
            // todo: should check validation
            TypeMeta f_type((std::get<2>(*_functions))());
            return f_type;
        }

        bool FieldAccessor::getTypeMeta(TypeMeta& field_type)
        {
            TypeMeta f_type(_field_type_name);
            field_type = f_type;
            return f_type._is_valid;
        }

        const char* FieldAccessor::getFieldName() const { return _field_name; }
        const char* FieldAccessor::getFieldTypeName() { return _field_type_name; }

        bool FieldAccessor::isArrayType()
        {
            // todo: should check validation
            return (std::get<5>(*_functions))();
        }

        FieldAccessor& FieldAccessor::operator=(const FieldAccessor& dest)
        {
            if (this == &dest)
            {
                return *this;
            }
            _functions       = dest._functions;
            _field_name      = dest._field_name;
            _field_type_name = dest._field_type_name;
            return *this;
        }

        MethodAccessor::MethodAccessor()
        {
            _method_name = k_unknown;
            _functions   = nullptr;
        }

        MethodAccessor::MethodAccessor(MethodFunctionTuple* functions) : _functions(functions)
        {
            _method_name      = k_unknown;
            if (_functions == nullptr)
            {
                return;
            }

            _method_name      = (std::get<0>(*_functions))();
        }
        const char* MethodAccessor::getMethodName() const{
            return (std::get<0>(*_functions))();
        }
        MethodAccessor& MethodAccessor::operator=(const MethodAccessor& dest)
        {
            if (this == &dest)
            {
                return *this;
            }
            _functions       = dest._functions;
            _method_name      = dest._method_name;
            return *this;
        }
        void MethodAccessor::invoke(void* instance) { (std::get<1>(*_functions))(instance); }
        ArrayAccessor::ArrayAccessor() :
                _func(nullptr), _array_type_name("UnKnownType"), _element_type_name("UnKnownType")
        {}

        ArrayAccessor::ArrayAccessor(ArrayFunctionTuple* array_func) : _func(array_func)
        {
            _array_type_name   = k_unknown_type;
            _element_type_name = k_unknown_type;
            if (_func == nullptr)
            {
                return;
            }

            _array_type_name   = std::get<3>(*_func)();
            _element_type_name = std::get<4>(*_func)();
        }
        const char* ArrayAccessor::getArrayTypeName() { return _array_type_name; }
        const char* ArrayAccessor::getElementTypeName() { return _element_type_name; }
        void        ArrayAccessor::set(int index, void* instance, void* element_value)
        {
            // todo: should check validation
            size_t count = getSize(instance);
            // todo: should check validation(index < count)
            std::get<0> (*_func)(index, instance, element_value);
        }

        void* ArrayAccessor::get(int index, void* instance)
        {
            // todo: should check validation
            size_t count = getSize(instance);
            // todo: should check validation(index < count)
            return std::get<1>(*_func)(index, instance);
        }

        int ArrayAccessor::getSize(void* instance)
        {
            // todo: should check validation
            return std::get<2>(*_func)(instance);
        }

        ArrayAccessor& ArrayAccessor::operator=(ArrayAccessor& dest)
        {
            if (this == &dest)
            {
                return *this;
            }
            _func              = dest._func;
            _array_type_name   = dest._array_type_name;
            _element_type_name = dest._element_type_name;
            return *this;
        }

        ReflectionInstance& ReflectionInstance::operator=(ReflectionInstance& dest)
        {
            if (this == &dest)
            {
                return *this;
            }
            _instance = dest._instance;
            _meta     = dest._meta;

            return *this;
        }

        ReflectionInstance& ReflectionInstance::operator=(ReflectionInstance&& dest)
        {
            if (this == &dest)
            {
                return *this;
            }
            _instance = dest._instance;
            _meta     = dest._meta;

            return *this;
        }
    } // namespace Reflection
} // namespace Movan