project "GLFW"
    kind "StaticLib"
    language "C"
    
    targetdir ("../../../bin/")
    objdir ("../../../bin_obj/")

    files
    {
        "include/GLFW/glfw3.h",
        "include/GLFW/glfw3native.h",
        "src/glfw_config.h",
        "include/GLFW/**/*.h",    -- Includes all header files in the GLFW include directory
        "include/*.h", 
        "src/*.c",
        "src/**/*.c"              -- Includes all source files in the src directory
    }
    --[[ 
        ***IMPORTANT!!!!***
        Never, ever put any thing global after filters, LUA is not python and indentations doesn't tell the script anything
        as soon as you put anything after the filter, it will be a part of that filter, taking the below line under filters,
        will hide them and the compilation might fail depending on the filter type 
    ]]

      includedirs
    {
      
    }

    filter "system:linux"
        pic "On"
        staticruntime "On"
        systemversion "latest"
        defines { "_GLFW_X11",
                    "GLFW_EXPOSE_NATIVE_X11" 
                }
        buildoptions { "-Wall", "-Wextra", "-fPIC", "-fdiagnostics-color=auto","-ggdb"  }

    filter {}
    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines 
        { 
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

        filter "configurations:Debug"
            runtime "Debug"
            targetsuffix "d"
            symbols "on"
    filter {}
        filter "configurations:Release"
            runtime "Release"
            optimize "on"
    filter {}
filter {}