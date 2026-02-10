project "spdlog"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    
    targetdir ("../../../bin/")
    objdir ("../../../bin_obj/")
    
    
    files
    {
        "include/spdlog/**",
    "src/*.cpp"
    }
    --[[ 
        ***IMPORTANT!!!!***
        Never, ever put any thing global after filters, LUA is not python and indentations doesn't tell the script anything
        as soon as you put anything after the filter, it will be a part of that filter, taking the below line under filters,
        will hide them and the compilation might fail depending on the filter type 
    ]]

    includedirs
    {
        "include/"
    }
    defines { "SPDLOG_COMPILED_LIB" }  --   this is for static builds
    filter "system:linux"
        pic "On"
        staticruntime "On"
        systemversion "latest"
        buildoptions { "-Wall", "-Wextra", "-fPIC", "-fdiagnostics-color=auto","-ggdb" , "-finput-charset=UTF-8", "-fexec-charset=UTF-8" }
 
    filter {}
    filter "system:windows"
        systemversion "latest"
        buildoptions { "/utf-8" 					  }  -- Add UTF-8 support

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