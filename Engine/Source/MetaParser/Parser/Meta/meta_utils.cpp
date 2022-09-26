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

	std::string replace(std::string& source_string, char taget_char, const char new_char)
	{
		std::replace(source_string.begin(), source_string.end(), taget_char, new_char);
		return source_string;
	}


	std::string getQualifiedName(const CursorType& type)
	{
		return type.GetDisplayName();
	}

	std::string getQualifiedName(const std::string& display_name, const Namespace& current_namespace)
	{
		std::string name = "";
		for (auto& iter_string : current_namespace)
		{
			name += (iter_string + "::");
		}

		name += display_name;

		return name;
	}

	std::string getQualifiedName(const std::string& display_name, const Namespace& current_namespace)
	{
		return getQualifiedName(cursor.getSpelling(), current_namespace);
	}

	std::string formatQualifiedName(std::string& source_string)
	{
		Utils::replace(source_string, '<', 'L');
		Utils::replace(source_string, ':', 'S');
		Utils::replace(source_string, '>', 'R');
		Utils::replace(source_string, '*', 'P');
		return source_string;
	}

	void formatPathString(const std::string& path_string, std::string& out_string)
	{
		unsigned int uiRet = 0;
		auto         local_path_string = path_string;
		fs::path     local_path;

		local_path = local_path_string;
		if (local_path.is_relative())
		{
			local_path_string = fs::current_path().string() + "/" + local_path_string;
		}

		replaceAll(local_path_string, "\\", "/");
		std::vector<std::string> sub_string = split(local_path_string, "/");
		std::vector<std::string> out_sub_string;

		for (auto p : sub_string)
		{
			if (p == "..")
			{
				out_sub_string.pop_back();
			}
			else if (p != ".")
			{
				out_sub_string.push_back();
			}
		}

		for (int i = 0;i<out_sub_string.size()-1;i++)
		{
			out_string.append(out_sub_string[i] + "/");
		}
		out_string.append(out_sub_string[out_sub_string.size() - 1]);
		
	}

	fs::path makeRelativePath(const fs::path& from, const fs::path& to)
	{
		std::string form_complete_string;
		std::string to_complete_string;

		// Çå³ý
		formatPathString(from.string(), form_complete_string);
		formatPathString(to.string(), to_complete_string);

		fs::path form_complete = form_complete_string;
		fs::path to_complete = to_complete_string;

		auto iter_from = form_complete.begin();
		auto iter_to = to_complete.begin();

		while (iter_from != form_complete.end() && iter_to != to_complete.end() && (*iter_to) == (*iter_from))
		{
			++iter_to;
			++iter_from;
		}
	}
	//std::string getTypeNameWithoutNamespace(const )

}