#pragma once
#include "../../MetaParser/Parser/Common/schema_module.h"

#include <functional>
#include <string>
namespace Generator
{
    class GeneratorInterface
    {
    public:
        GeneratorInterface(
            std::string                             out_path,
            std::string                             root_path,
            std::function<std::string(std::string)> get_include_func
        ) :
            out_path_(out_path),
            root_path_(root_path), get_include_func_(get_include_func)
        {}
        virtual int  generate(std::string path, SchemaMoudle schema) = 0;
        virtual void finish() {};

        virtual ~GeneratorInterface() {};

    protected:
        virtual void        prepareStatus(std::string path);
        virtual void        genClassRenderData(std::shared_ptr<Class> class_temp, Mustache::data& class_def);
        virtual void        genClassFieldRenderData(std::shared_ptr<Class> class_temp, Mustache::data& feild_defs);
        virtual std::string processFileName(std::string path) = 0;

        std::string                             out_path_{ "gen_src" };
        std::string                             root_path_;
        std::function<std::string(std::string)> get_include_func_;
    };
} // namespace Generator