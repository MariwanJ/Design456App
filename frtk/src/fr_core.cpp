//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2026
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

#include <fr_core.h>

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
       //std::filesystem::path dir = filePath.parent_path();
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
    // Function to convert string to enum
    const char* getCameraName(const uint8_t t) {
        return camNames[t];
    };

    // Function to convert string to enum
    uint8_t getCameraIndex(const char* name) {
        if (std::strcmp(name, "PERSPECTIVE")) return PERSPECTIVE;
        else if (std::strcmp(name,  "ORTHOGRAPHIC"))  return ORTHOGRAPHIC;
        else if (std::strcmp(name,  "TOP")         )  return  TOP;
        else if (std::strcmp(name,  "BOTTOM")      )  return BOTTOM;
        else if (std::strcmp(name,  "FRONT")       )  return FRONT;
        else if (std::strcmp(name,  "BACK")        )  return BACK;
        else if (std::strcmp(name,  "RIGHT")       )  return RIGHT;
        else if (std::strcmp(name,  "LEFT")        )  return LEFT;
        else throw std::invalid_argument("Invalid uint8_t name: " + std::string(name));
    }
}