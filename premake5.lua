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
IncludeDir["spdlog"] = "../frtk/vendor/spdlog/include"
IncludeDir["glm"] = "../frtk/vendor/glm"
IncludeDir["yaml-cpp"] = "../frtk/vendor/yaml-cpp"
IncludeDir["GLFW"] = "../frtk/vendor/GLFW/include"


---IncludeDir["stb_image"] = "frtk/vendor/stb_image"
--IncludeDir["ImGui"] = "frtk/vendor/imgui"



--Projects
--Include other lua scripts and group them as dependecies
group "Dependencies"
      include "frtk/vendor/GLFW"
      include "frtk/vendor/Glad"
	  include "frtk/vendor/spdlog"
	  include "frtk/vendor/yaml-cpp"

-- Projects
---group "Dependencies"
   --- includeexternal "frtk/vendor/Glad"
group ""

--to inlcude other lua scritp-project
include "frtk"
include "Design456App"