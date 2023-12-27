#include "Fr_Core.h"

namespace ResourcePath {
#if defined(_WIN32)

	std::string getExecutablePath() {
		char rawPathName[MAX_PATH];
		GetModuleFileNameA(NULL, rawPathName, MAX_PATH);
		return std::string(rawPathName);
	}

	std::string getExecutableDir() {
		std::string executablePath = getExecutablePath();
		char* exePath = new char[executablePath.length()];
		strcpy(exePath, executablePath.c_str());
		PathRemoveFileSpecA(exePath);
		std::string directory = std::string(exePath);
		delete[] exePath;
		return directory;
	}

	std::string mergePaths(std::string pathA, std::string pathB) {
		char combined[MAX_PATH];
		PathCombineA(combined, pathA.c_str(), pathB.c_str());
		std::string mergedPath(combined);
		return mergedPath;
	}
	bool checkIfFileExists(const std::string& filePath) {
		return true;
	}
	std::string exePath() {
		return "";
	}
	std::string meshPath() {
		return "";
	}
	std::string shaderPath()
	{
		return "";
	}
	std::string imgPath() {
		return "";
	}

#endif

#ifdef __linux__

	std::string getExecutablePath() {
		char rawPathName[PATH_MAX];
		realpath(PROC_SELF_EXE, rawPathName);
		return  std::string(rawPathName);
	}

	std::string getExecutableDir() {
		std::string executablePath = getExecutablePath();
		char* executablePathStr = new char[executablePath.length() + 1];
		strcpy(executablePathStr, executablePath.c_str());
		char* executableDir = dirname(executablePathStr);
		delete[] executablePathStr;
		return std::string(executableDir);
	}

	std::string mergePaths(std::string pathA, std::string pathB) {
		return pathA + "/" + pathB;
	}

#endif

#ifdef __APPLE__
	std::string getExecutablePath() {
		char rawPathName[PATH_MAX];
		char realPathName[PATH_MAX];
		uint32_t rawPathSize = (uint32_t)sizeof(rawPathName);

		if (!_NSGetExecutablePath(rawPathName, &rawPathSize)) {
			realpath(rawPathName, realPathName);
		}
		return  std::string(realPathName);
	}

	std::string getExecutableDir() {
		std::string executablePath = getExecutablePath();
		char* executablePathStr = new char[executablePath.length() + 1];
		strcpy(executablePathStr, executablePath.c_str());
		char* executableDir = dirname(executablePathStr);
		delete[] executablePathStr;
		return std::string(executableDir);
	}

	std::string mergePaths(std::string pathA, std::string pathB) {
		return pathA + "/" + pathB;
	}
#endif
};