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
         buildoptions {
         "-Wall",
         "-Wextra",
         "-Wconversion",
         "-Wfloat-conversion",
   ---      "-Werror",
         "-fPIC",
         "-ggdb",
         "-fdiagnostics-color=auto",
         "-finput-charset=UTF-8",
         "-fexec-charset=UTF-8"
      }

 
    filter {}
    filter "system:windows"
        systemversion "latest"
        buildoptions { "/external:W0", "/utf-8" }
        
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