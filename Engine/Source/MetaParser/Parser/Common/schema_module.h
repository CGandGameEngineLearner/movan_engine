#pragma once
#include "precompiled.h"

class Class;
class Global;
class Function;
class Enum;

struct SchemaModule//Ä£Ê½Ä£¿é
{
    std::string name;

    std::vector<std::shared_ptr<Class>> classes;
};