project "libgd"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.c",
        "src/**.cpp",
    }
    
    defines
    {
       "FOR_MSW",
       "WIN32",
        "_WINDOWS",
        "HAVE_CONFIG_H",
        "_WIN32",
        "MSWIN32",
        "BGDWIN32",
        "WINVER=0x0500",
        "_WIN32_WINNT=0x0500",
        "_WIN32_IE=0x0600",
        "_CRT_SECURE_NO_DEPRECATE",
        "libgd_EXPORTS",
        "HAVE_LIBXPM", --- XPM SUPPORT for libgd
    }
        
        
    includedirs
    {
    "src",
     "msinttypes/"
    }
    
    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
        
	filter "configurations:Debug"
		defines "FR_DEBUG"
		runtime "Debug"
		symbols "on"
        links 
		{  

        }
        
	filter "configurations:Release"
		defines "FR_RELEASE"
		runtime "Release"
		optimize "on"
        links 
		{  
        }