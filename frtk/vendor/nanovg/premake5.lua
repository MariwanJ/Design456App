project "nanovg"
    language "C"
    kind "StaticLib"
	staticruntime "on"
	 
	targetdir ("../../../bin/")
    objdir ("../../../bin_obj/")
    
    files { 
	"src/*.c",
    "src/*.h",

    "obsolete/*.c",
    "obsolete/*.h",
	}
	includedirs { 
	"src",
	"obsolete"
	}
	
    filter "system:linux"
        pic "On"
        staticruntime "On"
        systemversion "latest"
        buildoptions { "-Wall", "-Wextra", "-fPIC", "-fdiagnostics-color=auto","-ggdb" }
 
    filter {}
    filter "system:windows"
        systemversion "latest"
        buildoptions { "/utf-8" }  -- Add UTF-8 support

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