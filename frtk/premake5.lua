project "frtk"
	kind "StaticLib"--kind "SharedLib" 
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	--runtime "Debug"
	
	
--[[  			-- To use /MT in premake:
			staticruntime "on"
			runtime "Release"

			--To use /MTd in premake:
			staticruntime "on"
			runtime "Debug"

			--To use /MD in premake:
			staticruntime "off"
			runtime "Release"

			--To use /MDd in premake:
			staticruntime "off"
			runtime "Debug"  ]]
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	--- dosen't work for now .. fix it later
	---pchheader "frtk.h"             --preheader
	---pchsource "src/frtk.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"src/**.cxx",
        
		--"vendor/glm/glm/**.hpp",
		--"vendor/glm/glm/**.inl",
      ---  "vendor/stb_image/**.h",
		---"vendor/stb_image/**.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE",
		"GLFW_EXPOSE_NATIVE_WIN32",
		"FRTK_ENABLE_ASSERTS",
		"GLAD_GL_IMPLEMENTATION",
		"FL_INTERNALS",
		"FL_LIBRARY",
		"_USE_MATH_DEFINES",	--MS MATH reauire this M_PI for example
		"FRTK_ENABLE_ASSERTS"  ---debug break enable
	}

	includedirs
	{
        "%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
        "%{IncludeDir.imGui}",
		"%{IncludeDir.glm}",
		"$(SolutionDir)frtk/vendor/spdlog/include",
		"src",
		"$(SolutionDir)frtk/vendor/instrumentation",
		--"%{IncludeDir.yaml-cpp}",
        --"%{IncludeDir.ImGui}",
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
            "glu32",
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
			"Glad",
			"glu32.lib",
			"gdiplus.lib",
		  --"ImGui",
		  --"yaml-cpp",
			"opengl32.lib",
			"GLFW",
			"Glad",
		}

	filter "configurations:Release"
		defines "FR_RELEASE"
		runtime "Release"
		optimize "on"
        links 
		{   "opengl32",
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
            "fltk",
			"Glad",
			"gdiplus.lib",
		  --"ImGui",
		  --"yaml-cpp",
			"opengl32.lib",
			"GLFW",
			"Glad",
		
    }