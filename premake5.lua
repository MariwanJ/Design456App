-- Design456App
workspace "Design456App"
	architecture "x64"
	startproject "Design456App"
    
	configurations
	{
		"Debug",
		"Release"
	}
	
	flags
	{
		"MultiProcessorCompile",
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

-- Include directories relative to frtk
IncludeDir = {}
IncludeDir["Glad"] = "../frtk/vendor/Glad/include"
IncludeDir["imGui"] = "../frtk/vendor/imGui/src"
IncludeDir["ImGuizmo"] = "../frtk/vendor/ImGuizmo/src"
IncludeDir["spdlog"] = "../frtk/vendor/spdlog/include"
IncludeDir["glm"] = "../frtk/vendor/glm"
IncludeDir["yaml-cpp"] = "../frtk/vendor/yaml-cpp"
IncludeDir["GLFW"] = "../frtk/vendor/GLFW/include"
IncludeDir["stb_image"] = "../frtk/vendor/stb_image/src"
IncludeDir["objloader"] = "../frtk/vendor/objloader"
IncludeDir["EnTT"] = "../frtk/vendor/EnTT"

--Projects
--Include other lua scripts and group them as dependencies
group "Dependencies"
	include "frtk/vendor/GLFW"
	include "frtk/vendor/Glad"
	include "frtk/vendor/imGui"
	include "frtk/vendor/ImGuizmo"
	include "frtk/vendor/spdlog"
	include "frtk/vendor/yaml-cpp"
	include "frtk/vendor/stb_image"
	include "frtk/vendor/objloader"  
		

-- Don't remove below line. Without this, the following names will be grouped as dependencies.
group ""

--to include other lua script-project
include "Design456App"
include "frtk"