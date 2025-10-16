project "objloader"
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
        "../../vendor/glm/",
        "src"
    }
    
    filter "system:linux"
        pic "On"
        staticruntime "On"
        systemversion "latest"
                buildoptions { "-Wall", "-Wextra", "-fPIC", "-fdiagnostics-color=auto" }

        filter "configurations:Debug"
            buildoptions { "-ggdb" }  

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        targetsuffix "d"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
