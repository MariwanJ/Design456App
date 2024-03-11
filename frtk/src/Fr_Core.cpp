#include "Fr_Core.h"
namespace FR {
	std::string separateFN(std::string& st) {
#ifdef _WIN32
		const char PATH_SEPARATOR = '\\';
#else
		const char PATH_SEPARATOR = '/';
#endif

		std::replace(st.begin(), st.end(), '\\', PATH_SEPARATOR);
 
		// Use std::filesystem to get directory and file
		std::filesystem::path filePath(st);
		std::filesystem::path dir = filePath.parent_path();
		std::filesystem::path file = filePath.filename();

		// Convert back to strings if needed
	   // std::string dirStr = dir.generic_string();
		std::string fileStr = file.generic_string();
		size_t lastDotIndex = fileStr.find_last_of(".");
		if (lastDotIndex != std::string::npos) {
			return fileStr.substr(0, lastDotIndex);
		}
		return fileStr;
	}
}