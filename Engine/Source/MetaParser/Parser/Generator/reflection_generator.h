#pragma once
#include "generator.h"
namespace Generator
{
	class ReflectionGenerator :public GeneratorInterface
	{
	public:
		ReflectionGenerator() = delete;
		ReflectionGenerator(std::string d);
	};
}