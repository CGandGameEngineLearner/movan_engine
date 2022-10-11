#include <filesystem>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>

#include "Source/Runtime/engine.h"

int main()
{
	std::filesystem::path executable_path(argv[0]);
	std::filesystem::path config_file_path = executable_path.parent_path() / "MovanEditor.ini";

	Movan::MovanEngine* engine = new Movan::MovanEngine();//初始化引擎

	engine->startEngine(config_file_path.generic_string());
	engine->initialize();


}