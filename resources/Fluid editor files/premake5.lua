

--[[
        Creating Make file or visual studio project automatically
--]]

workspace "testPreemake"
        architecture "x64"

       configurations 
       { 
            "Debug",
            "Release" 
        }
 outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
 
 project "testPreemake"
       location "testPreemake"
       kind "ConsoleApp"
       language "C++"
  
       targetdir ("bin/"..outputdir.."/%{prj.name}")
       objdir ("bin-int/"..outputdir.."/%{prj.name}")

       files{
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
       }
      includedirs
      {
        "%{prj.name}/src/",
		"%{prj.name}../fltk-1.3.4-2/"
      }
      filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        defines
        {
            "TESTPREEMAKE_PLATFORM_WINDOWS"
        }

      filter { "configurations:Debug" }
          defines { "DEBUG" }
          symbols "On"

       filter { "configurations:Release" }
          defines { "NDEBUG" }
          optimize "On"

      filter{"system:windows","configurations:Release"}
            buildoptions "/MT"
            