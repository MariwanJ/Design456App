project "ImGuizmo"
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
     defines
     {
         "IMGUI_DEFINE_MATH_OPERATORS"
     }
    --[[ 
        ***IMPORTANT!!!!***
        Never, ever put any thing global after filters, LUA is not python and indentations doesn't tell the script anything
        as soon as you put anything after the filter, it will be a part of that filter, taking the below line under filters,
        will hide them and the compilation might fail depending on the filter type 
    ]]
    includedirs
    {
        "../../vendor/GLFW/include",
        "../../vendor/Glad/include",
        "../../vendor/imGui/src",
        "src"
    }
    filter "system:linux"
        pic "On"
        staticruntime "On"
        systemversion "latest"
                buildoptions { "-Wall", "-Wextra", "-fPIC", "-fdiagnostics-color=auto","-ggdb" }
    filter {}
    
    filter "system:windows"
        systemversion "latest"

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