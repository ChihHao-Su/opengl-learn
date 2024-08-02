#ifndef FILE_HXX
#define FILE_HXX

#include <string>
#include <string_view>
#include <filesystem>

namespace Essentials::File {
	std::string read(const std::filesystem::path& file);
}

#endif // !FILE_HXX
