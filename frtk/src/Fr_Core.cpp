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