#include "serializer.h"
#include<assert.h>

namespace Movan
{
    template<>
    MJson MSerializer::write(const char& instance)
    {
        return MJson(instance);
    }
    template<>
    char& MSerializer::read(const MJson& json_context, char& instance)
    {
        assert(json_context.is_number());
        return instance = json_context.number_value();
    }

    template<>
    MJson MSerializer::write(const int& instance)
    {
        return MJson(instance);
    }
    template<>
    int& MSerializer::read(const MJson& json_context, int& instance)
    {
        assert(json_context.is_number());
        return instance = static_cast<int>(json_context.number_value());
    }

    template<>
    MJson MSerializer::write(const unsigned int& instance)
    {
        return MJson(static_cast<int>(instance));
    }
    template<>
    unsigned int& MSerializer::read(const MJson& json_context, unsigned int& instance)
    {
        assert(json_context.is_number());
        return instance = static_cast<unsigned int>(json_context.number_value());
    }

    template<>
    MJson MSerializer::write(const float& instance)
    {
        return MJson(instance);
    }
    template<>
    float& MSerializer::read(const MJson& json_context, float& instance)
    {
        assert(json_context.is_number());
        return instance = static_cast<float>(json_context.number_value());
    }

    template<>
    MJson MSerializer::write(const double& instance)
    {
        return MJson(instance);
    }
    template<>
    double& MSerializer::read(const MJson& json_context, double& instance)
    {
        assert(json_context.is_number());
        return instance = static_cast<float>(json_context.number_value());
    }

    template<>
    MJson MSerializer::write(const bool& instance)
    {
        return MJson(instance);
    }
    template<>
    bool& MSerializer::read(const MJson& json_context, bool& instance)
    {
        assert(json_context.is_bool());
        return instance = json_context.bool_value();
    }

    template<>
    MJson MSerializer::write(const std::string& instance)
    {
        return MJson(instance);
    }
    template<>
    std::string& MSerializer::read(const MJson& json_context, std::string& instance)
    {
        assert(json_context.is_string());
        return instance = json_context.string_value();
    }
}//namespace Movan