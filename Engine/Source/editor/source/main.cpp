#pragma once
#include <filesystem>


import MovanEngine;


// https://gcc.gnu.org/onlinedocs/cpp/Stringizing.html
#define MOVAN_XSTR(s) MOVAN_STR(s)
#define MOVAN_STR(s) #s

int main(int argc, char** argv)
{
    std::filesystem::path executable_path(argv[0]);

    std::filesystem::path config_file_path = executable_path.parent_path() / "MovanEditor.ini";

    std::unique_ptr<Movan::MovanEngine> engine = std::make_unique<Movan::MovanEngine>();//初始化引擎

    engine->startEngine(config_file_path.generic_string());
    engine->initialize();


}