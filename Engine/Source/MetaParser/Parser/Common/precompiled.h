#pragma once

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../../../../ThirdParty/LLVM/include/clang-c/Index.h"

namespace fs = std::filesystem;

#include "../Meta/meta_data_config.h"
#include "../Meta/meta_utils.h"

#include "../../../../ThirdParty/mustache/mustache.hpp"

namespace Mustache = kainjow::mustache;