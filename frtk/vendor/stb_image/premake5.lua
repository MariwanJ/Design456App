project "stb_image"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    
    targetdir ("../../../bin/")
    objdir ("../../../bin_obj/")
    
    
    files
    {
        "src/*.h",
        "src/*.c",
        "src/*.cpp",
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
    
    defines
   {
        "STB_IMAGE_IMPLEMENTATION=1"
    }
    filter "system:linux"
        pic "On"
        staticruntime "On"
        systemversion "latest"
         buildoptions {
         "-Wall",
         "-Wextra",
         "-Wconversion",
         "-Wfloat-conversion",
         "-Werror",
         "-fPIC",
         "-ggdb",
         "-fdiagnostics-color=auto",
         "-finput-charset=UTF-8",
         "-fexec-charset=UTF-8"
      }

 
    filter {}

    filter "system:windows"
        systemversion "latest"
        buildoptions { "/W4", "/utf-8" }

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