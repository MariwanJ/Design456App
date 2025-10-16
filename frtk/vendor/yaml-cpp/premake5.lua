project "yaml-cpp"
    kind "StaticLib"
    language "C++"
    staticruntime "on"

    targetdir ("../../../bin/")
    objdir ("../../../bin_obj/")

    files
    {
        "include/yaml-cpp/**",
        "src/**"
    }

    includedirs
    {
        "include"
    }

    defines { "YAML_CPP_STATIC_DEFINE" }  -- Ensure static definition is set

    filter "system:linux"
        pic "On"
        staticruntime "On"
        systemversion "latest"
        buildoptions { "-Wall", "-Wextra", "-fPIC", "-fdiagnostics-color=auto" }

        filter "configurations:Debug"
            buildoptions { "-ggdb" } 


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