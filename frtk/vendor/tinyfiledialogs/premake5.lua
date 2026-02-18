project "tinyfiledialogs"
    language "C"
    kind "StaticLib"
	staticruntime "on"
	 
	targetdir ("../../../bin/")
    objdir ("../../../bin_obj/")
    

    files { 
	"src/*.c",
        "src/*.h",
	}
	includedirs { 
	"src",
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