-- Design456App
workspace "Design456App"
    architecture "x64"
    startproject "Design456App"
	multiprocessorcompile "on"
    

    configurations
    {
        "Debug",
        "Release"
    }

  
    -- Set a single output directory
    outputdir = "bin/"
    debugdir (outputdir)  -- This sets the working directory to bin/

    -- Include directories relative to frtk
    IncludeDir = {}
    IncludeDir["Glad"]      = "../frtk/vendor/Glad/include"
    IncludeDir["imGui"]     = "../frtk/vendor/imGui/src"
    IncludeDir["ImGuizmo"]  = "../frtk/vendor/ImGuizmo/src"
    IncludeDir["spdlog"]    = "../frtk/vendor/spdlog/include"
    IncludeDir["glm"]       = "../frtk/vendor/glm"
    IncludeDir["yaml-cpp"]  = "../frtk/vendor/yaml-cpp"
    IncludeDir["GLFW"]      = "../frtk/vendor/GLFW/include"
    IncludeDir["stb_image"] = "../frtk/vendor/stb_image/src"
    IncludeDir["objloader"] = "../frtk/vendor/objloader"
    IncludeDir["OpenMesh"]  = "../frtk/vendor/OpenMesh/src"
    IncludeDir["freetype"]  = "../frtk/vendor/freetype/include"
    IncludeDir["nanovg"]  = "../frtk/vendor/nanovg/src"
    IncludeDir["tinyfiledialogs"]  = "../frtk/vendor/tinyfiledialogs/src"


-- Configure projects
project "Design456App"
    kind "ConsoleApp"
    language "C++"

    targetdir (outputdir )  -- Will output to bin
    objdir ("bin_obj/")  -- Object files also in respective folders
    
    

--[[         files
        {
            "src/**.cpp",
            "include/**.h"
        } ]]
    --[[ 
        ***IMPORTANT!!!!***
        Never, ever put any thing global after filters, LUA is not python and indentations doesn't tell the script anything
        as soon as you put anything after the filter, it will be a part of that filter, taking the below line under filters,
        will hide them and the compilation might fail depending on the filter type 
    ]]
    includedirs
    {
        IncludeDir["Glad"],
        IncludeDir["GLFW"],
        IncludeDir["imGui"],
        IncludeDir["ImGuizmo"],
        IncludeDir["objloader"],
        IncludeDir["OpenMesh"],
        IncludeDir["spdlog"],
        IncludeDir["stb_image"],
        IncludeDir["yaml-cpp"],
        IncludeDir["freetype"],
        IncludeDir["nanovg"],
        IncludeDir["tinyfiledialogs"],
    }

    filter "configurations:Debug"
        targetname "Design456AppD"  -- Append 'D' for Debug builds
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        targetname "Design456App"   -- No suffix for Release builds
        defines { "NDEBUG" }
        optimize "On"

        
-- Projects
-- Include other lua scripts and group them as dependencies
group "Dependencies"
        include "frtk/vendor/GLFW"
        include "frtk/vendor/Glad"
        include "frtk/vendor/imGui"
        include "frtk/vendor/ImGuizmo"
        include "frtk/vendor/spdlog"
        include "frtk/vendor/yaml-cpp"
        include "frtk/vendor/stb_image"
        include "frtk/vendor/objloader"
        include "frtk/vendor/OpenMesh"
        include "frtk/vendor/freetype"
        include "frtk/vendor/nanovg"
        include "frtk/vendor/tinyfiledialogs"

    -- Don't remove the below line. Without this, the following names will be grouped as dependencies.
group ""
    -- To include other lua script-projects
    include "Design456App"
    include "frtk"
