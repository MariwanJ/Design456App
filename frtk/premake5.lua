project "frtk"
    kind "StaticLib"
    language "C"
    cppdialect "C++17"
    staticruntime "on"
    
    
    --[[       Note: Windows Only
            To use /MT in premake:
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

    -- WARNING!!! : put these definitions that will be applied to all configuration before having any filter
    --              Otherwise they will go under the filter. This is not a python. Lua doesn't care about spaces.
    --              Having these under filter xxxx will be applied ONLY for that filter.
    --              This is important to notice otherwise it will be wrong.!!!

    local cwd = os.getcwd()
    project_root = cwd:gsub("/[^/]+$", "")  -- removes the last path component

    -- Output directories for both windows and linux
    targetdir ("../bin/")
    objdir ("../bin_obj/")

    -- Uncomment if using precompiled headers
    -- pchheader "frtk.h"
    -- pchsource "src/frtk.cpp"

    -- Source files from the /src folder
    files
    {
        "src/**.h",
        "src/**.cpp",
        "src/**.cxx",
        "src/**.c"
    }
    --[[ 
        ***IMPORTANT!!!!***
        Never, ever put any thing global after filters, LUA is not python and indentations doesn't tell the script anything
        as soon as you put anything after the filter, it will be a part of that filter, taking the below line under filters,
        will hide them and the compilation might fail depending on the filter type 
    ]]
    -- Include directories
    includedirs
    {
        "src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imGui}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.ImGuizmo}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.OpenMesh}",
        "%{IncludeDir.objloader}",
        "%{IncludeDir.freetype}",
        "%{IncludeDir.nanovg}",
		"%{IncludeDir.tinyfiledialogs}",
        "$(SolutionDir)frtk/vendor/instrumentation"
    }

    -- Shared defines (cross-platform)
    defines
    {
        "IMGUI_DEFINE_MATH_OPERATORS",
        "GLM_ENABLE_EXPERIMENTAL",
        "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",
        "_CRT_SECURE_NO_WARNINGS",
        "_USE_MATH_DEFINES",
        "GLFW_INCLUDE_NONE",
        "FRTK_ENABLE_ASSERTS"
    }

    libdirs
    {
        "../bin/"
    }

    -- Windows-specific
    filter "system:windows"
        systemversion "latest"
        buildoptions { "/W4", "/utf-8" }        systemversion "latest"
        defines
        {
            "GLFW_EXPOSE_NATIVE_WIN32",
            "FRTK_PLATFORM_WINDOWS",
            "FR_BUILD_STATIC"
        }
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
            "Glad%{cfg.targetsuffix}",
            "GLFW%{cfg.targetsuffix}",
            "imGui%{cfg.targetsuffix}",
            "ImGuizmo%{cfg.targetsuffix}",
            "objloader%{cfg.targetsuffix}",
            "OpenMesh%{cfg.targetsuffix}",
            "spdlog%{cfg.targetsuffix}",
            "stb_image%{cfg.targetsuffix}",
            "yaml-cpp%{cfg.targetsuffix}",
            "freetype%{cfg.targetsuffix}",
            "nanovg%{cfg.targetsuffix}",
			"tinyfiledialogs%{cfg.targetsuffix}",
        }
    filter {}
    -- Linux-specific
    filter "system:linux"
        buildoptions { "-Wall", "-Wextra","-fPIC", "-fdiagnostics-color=auto","-ggdb" , "-finput-charset=UTF-8", "-fexec-charset=UTF-8" }
        defines
        {
            "GLFW_EXPOSE_NATIVE_X11",
            "FRTK_PLATFORM_LINUX"
        }
        links
        {
            "GL",        -- OpenGL
            "dl",        -- Dynamic loading for GLAD
            "pthread",   -- Required by GLFW
        }

    -- Debug configuration
    filter "configurations:Debug"
        defines "FR_DEBUG"
        runtime "Debug"
        targetsuffix "d"
        symbols "on"
    filter {}
    -- Release configuration
    filter "configurations:Release"
        defines "FR_RELEASE"
        runtime "Release"
        optimize "on"
    filter {}
filter {}

--- Combine join two libraries into one library
filter "system:linux"
    postbuildcommands {
    print("Current Working Directory: " .. cwd),  -- Debug output
---   print("library is: " .. project_root .. "/bin &&  ar -x " .. (project_root .. "/bin/libfrtk%{cfg.targetsuffix}.a")),  
    "echo Combine all libraries to one library",
    "cd " .. project_root .. "/bin &&  ar -x " .. (project_root .. "/bin/libfrtk%{cfg.targetsuffix}.a"       ),
    "cd " .. project_root .. "/bin &&  rm -fr " .. (project_root .. "/bin/libfrtk%{cfg.targetsuffix}.a"       ),--We need to remove it 
    "cd " .. project_root .. "/bin &&  ar -x " .. (project_root .. "/bin/libGlad%{cfg.targetsuffix}.a"       ),
    "cd " .. project_root .. "/bin &&  ar -x " .. (project_root ..  "/bin/libimGui%{cfg.targetsuffix}.a"      ),
    "cd " .. project_root .. "/bin &&  ar -x " .. (project_root ..  "/bin/libImGuizmo%{cfg.targetsuffix}.a"   ),
    "cd " .. project_root .. "/bin &&  ar -x " .. (project_root ..  "/bin/libspdlog%{cfg.targetsuffix}.a"     ),
    "cd " .. project_root .. "/bin &&  ar -x " .. (project_root ..  "/bin/libyaml-cpp%{cfg.targetsuffix}.a"   ),
    "cd " .. project_root .. "/bin &&  ar -x " .. (project_root ..  "/bin/libGLFW%{cfg.targetsuffix}.a"       ),
    "cd " .. project_root .. "/bin &&  ar -x " .. (project_root ..  "/bin/libstb_image%{cfg.targetsuffix}.a"  ),
    "cd " .. project_root .. "/bin &&  ar -x " .. (project_root ..  "/bin/libobjloader%{cfg.targetsuffix}.a"  ),
    "cd " .. project_root .. "/bin &&  ar -x " .. (project_root ..  "/bin/libOpenMesh%{cfg.targetsuffix}.a"   ),
    "cd " .. project_root .. "/bin &&  ar -x " .. (project_root ..  "/bin/libfreetype%{cfg.targetsuffix}.a"   ),
    "cd " .. project_root .. "/bin &&  ar -x " .. (project_root ..  "/bin/libnanovg%{cfg.targetsuffix}.a"   ),
	"cd " .. project_root .. "/bin &&  ar -x " .. (project_root ..  "/bin/tinyfiledialogs%{cfg.targetsuffix}.a"   ),
    "cd " .. project_root .. "/bin &&  ar -rcs " .. (project_root  .. "/bin/libfrtk%{cfg.targetsuffix}.a ") .. (project_root  .. "/bin/*.o" ),          --create static lib 
    "cd " .. project_root .. "/bin &&  g++ -shared -o " .. (project_root  .. "/bin/libfrtk%{cfg.targetsuffix}.so ") .. (project_root  .. "/bin/*.o" ),  --create shared lib also.
    "cd " .. project_root .. "/bin &&  rm -f " .. (project_root  .. "/bin/*.o" ),         -- Remove temporary object files
}

-- Group dependencies
group "Dependencies"
        include "frtk/vendor/GLFW"
        include "frtk/vendor/Glad"
        include "frtk/vendor/imGui"
        include "frtk/vendor/ImGuizmo"
        include "frtk/vendor/spdlog"
        include "frtk/vendor/yaml-cpp"
        include "frtk/vendor/stb_image"
        include "frtk/vendor/objloader"
        include "frtk/vendor/OpenMesh"
        include "frtk/vendor/freetype"
        include "frtk/vendor/nanovg"
		include "frtk/vendor/tinyfiledialogs"

-- Reset group
group ""
    include "frtk"