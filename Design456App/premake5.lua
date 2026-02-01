project "Design456App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    -- Output directories
    targetdir "../bin/"
    objdir "../bin_obj/"

    -- Source files
    files { 
        "src/**.h", 
        "src/**.cpp" 
    }

    -- Include directories
    includedirs {
        "../frtk/src",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imGui}",
        "%{IncludeDir.ImGuizmo}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.OpenMesh}",
        "%{IncludeDir.freeImage}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.objloader}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.freetype}",
        "%{IncludeDir.nanovg}",
    }

    -- Common defines
    defines {
        "GLFW_INCLUDE_NONE",
        "FRTK_ENABLE_ASSERTS",
        "_USE_MATH_DEFINES",
        "GLAD_GL_IMPLEMENTATION"
    }

    -- Library directories
    libdirs {
        "../bin/lib/"
    }

    -- Multi-threaded compile
    flags { "MultiProcessorCompile" }

    -- Common links
    local commonLinks = {
        "frtk",
    }

    ------------------------------
    -- CONFIGURATION FILTERS
    ------------------------------

    filter "configurations:Debug"
        defines { "FRTK_DEBUG" }
        runtime "Debug"
        symbols "on"
        links { commonLinks }

    filter "configurations:Release"
        defines { "FRTK_RELEASE" }
        runtime "Release"
        optimize "on"
        links { commonLinks }

    ------------------------------
    -- PLATFORM FILTERS
    ------------------------------

    -- Windows-specific
    filter "system:windows"
        defines { "FRTK_PLATFORM_WINDOWS", "GLFW_EXPOSE_NATIVE_WIN32" }
        links { "opengl32.lib", "gdiplus.lib" }

    -- Linux-specific
    filter "system:linux"
        defines { "FRTK_PLATFORM_LINUX" }
        buildoptions { "-Wall", "-Wextra", "-fPIC", "-fdiagnostics-color=auto" }
        links {
            "GL",
            "dl",
            "pthread",
            "X11",
            "Xrandr",
            "Xinerama",
            "Xxf86vm",
            "Xcursor",
            commonLinks
        }

    -- Reset filters. Always clear filters after each section 
    filter {}
