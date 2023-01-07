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
        "../frtk/vendor/spdlog/include",
        "../frtk/vendor/fltk",
		"../frtk/src",
        "%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
     ---"../frtk/vendor/%{IncludeDir.ImGui}"
	}
	defines{
		"GLFW_EXPOSE_NATIVE_WIN32",
		"GLFW_INCLUDE_NONE",
		"FRTK_ENABLE_ASSERTS" ,
		"GLAD_GL_IMPLEMENTATION",
		"FL_INTERNALS",
		"FL_LIBRARY"
	}

	flags
	{
		"MultiProcessorCompile",
	}

	libdirs {"../frtk/vendor/fltk/build/lib/Debug"}
	links 
	{   "frtk",
		"fltkd",
		"Glad",
		"opengl32.lib",
		"fltk_imagesd",
		"fltk_gld",
		"fltk_formsd",
		"opengl32.lib",
		"glu32.lib",
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