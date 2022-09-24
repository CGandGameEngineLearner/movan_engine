#pragma once
#include "Common/precompiled.h"
#include "Common/namespace.h"
#include "Common/schema_module.h"
#include "Cursor/cursor.h"
#include "Generator/generator.h"
#include "TemplateManager/template_manager.h"

class Class;

class MetaParser
{
public:
    static void prepare(void);

    MetaParser(const std::string project_input_file,
        const std::string include_file_path,
        const std::string include_path,
        const std::string include_sys,
        const std::string module_name,
        bool              is_show_errors);
    ~MetaParser(void);
    void finish(void);
    int  parse(void);
    void generateFiles(void);

private:
    std::string project_input_file_;

    std::vector<std::string> work_paths_;
    std::string              module_name_;
    std::string              sys_include_;
    std::string              source_include_file_name_;

    CXIndex           index_;
    CXTranslationUnit translation_unit_;

    std::unordered_map<std::string, std::string>  type_table_;
    std::unordered_map<std::string, SchemaMoudle> schema_modules_;

    std::vector<const char*>                    arguments = { {"-x",
                                           "c++",
                                           "-std=c++11",
                                           "-D__REFLECTION_PARSER__",
                                           "-DNDEBUG",
                                           "-D__clang__",
                                           "-w",
                                           "-MG",
                                           "-M",
                                           "-ferror-limit=0",
                                           "-o clangLog.txt"} };
    std::vector<Generator::GeneratorInterface*> generators_;

    bool is_show_errors_;

private:
    bool        parseProject(void);
    void        buildClassAST(const Cursor& cursor, Namespace& current_namespace);
    std::string getIncludeFile(std::string name);
};