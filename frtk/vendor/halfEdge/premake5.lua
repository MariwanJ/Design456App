project "halfEdge"
	kind "StaticLib"--kind "SharedLib" 
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	--runtime "Debug"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	

	files
	{
		"src/**.h",
		"src/**.cpp",
		"src/**.c",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE",
		"GLFW_EXPOSE_NATIVE_WIN32",
		"GLAD_GL_IMPLEMENTATION",
		"_USE_MATH_DEFINES",	---MS MATH reauire this M_PI for example
		"FRTK_ENABLE_ASSERTS",  ---debug break enable
	}
    libdirs {
    }
	includedirs
	{
        "%{IncludeDir.freeglut}",
		---"C:/freeglut/include"
	}
	filter "system:windows"
		systemversion "latest"
		defines
		{
            "FRTK_PLATFORM_WINDOWS",
			--"FR_BUILD_DLL",
			"FR_BUILD_STATIC",
			"GLFW_EXPOSE_NATIVE_WIN32",
			'GLFW_INCLUDE_NONE ',
			"FRTK_ENABLE_ASSERTS"
		}

	filter "configurations:Debug"
		defines "FR_DEBUG"
		runtime "Debug"
		symbols "on"
        links 
		{   
            "opengl32",
            "gdiplus",
            "comctl32",
            "ws2_32",
            "kernel32",
            "user32",
            "gdi32",
            "winspool",
            "shell32",
            "ole32",
            "oleaut32",
            "uuid",
            "comdlg32",
            "advapi32",
			"freeglut_static"
		}

	filter "configurations:Release"
		defines "FR_RELEASE"
		runtime "Release"
		optimize "on"
        links 
		{  
            "opengl32",
            "gdiplus",
            "comctl32",
            "ws2_32",
            "kernel32",
            "user32",
            "gdi32",
            "winspool",
            "shell32",
            "ole32",
            "oleaut32",
            "uuid",
            "comdlg32",
            "advapi32",
			"GLFW",
			"Glad",
			"freeglut_static"
    }