//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2024
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//
#include <fr_path.h>
namespace ResourcePath {
#if defined(_WIN32)

    std::string getExecutablePath() {
        char rawPathName[MAX_PATH];
        GetModuleFileNameA(NULL, rawPathName, MAX_PATH);
        return std::string(rawPathName);
    }

    std::string getExecutableDir() {
        std::string executablePath = getExecutablePath();
        char* exePath_ = new char[executablePath.length()];
        strcpy(exePath_, executablePath.c_str());
        PathRemoveFileSpecA(exePath_);
        std::string directory = std::string(exePath_);
        delete[] exePath_;
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