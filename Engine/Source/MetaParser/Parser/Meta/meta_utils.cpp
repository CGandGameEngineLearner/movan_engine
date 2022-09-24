#include "../Common/precompiled.h"
#include "meta_utils.h"

static int parse_flag = 0;

namespace Utils
{
	void toString(const CXString& str, std::string& output)
	{
		auto cstr = clang_getCString(str);

		output = cstr;

		clang_disposeString(str);
	}

	std::string getQualifiedName(const CursorType& type)
	{
		return type.GetDisplayName();
	}

	//std::string getTypeNameWithoutNamespace(const )

}