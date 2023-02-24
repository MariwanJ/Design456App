project "Design456App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"
	runtime "Debug"
	
	--[[
			To use /MT in premake:
			staticruntime "on"
			runtime "Release"

To use /MTd in premake:
			staticruntime "on"
			runtime "Debug"

			To use /MD in premake:
			staticruntime "off"
			runtime "Release"

			To use /MDd in premake:
			staticruntime "off"
			runtime "Debug"
	]]--

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imGui}",
		"%{IncludeDir.ImGuizmo}",
        "%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
        
        "../frtk/vendor/spdlog/include",
		"../frtk/src",
        
	}
	defines{
		"GLFW_EXPOSE_NATIVE_WIN32",
		"GLFW_INCLUDE_NONE",
		"FRTK_ENABLE_ASSERTS" ,
		"GLAD_GL_IMPLEMENTATION",
		"FL_INTERNALS",
		"FL_LIBRARY",
		"FRTK_ENABLE_ASSERTS"  ---debug break enable  
	}


	flags
	{
		"MultiProcessorCompile",
	}
	filter "configurations:Debug"
		links 
		{   "frtk",
			"Glad",
            "imGui",
            "ImGuizmo",
			"opengl32.lib",
			"gdiplus.lib",
			"GLFW",
			"opengl32.lib"
		}
	
	filter "configurations:Release"
		links 
		{   "frtk",
			"Glad",
            "imGui",
            "ImGuizmo",
			"opengl32.lib",
			"opengl32.lib",
			"gdiplus.lib",
			"GLFW",
			"opengl32.lib"
		}
	


	filter "system:windows"
		systemversion "latest"

		defines
		{
			"FRTK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FRTK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FRTK_RELEASE"
		runtime "Release"
        optimize "on"