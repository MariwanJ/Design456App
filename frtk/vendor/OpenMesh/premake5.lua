project "OpenMesh"
    kind "StaticLib"
    language "C++"            -- changed to C++ since you include .cpp files
    cppdialect "C++17"       -- set a C++ standard (adjust if you need another)

    targetdir ("../../../bin/")
    objdir ("../../../bin_obj/")
    
    
    files
    {
        -- headers
        "src/OpenMesh/*.h*",
        "src/OpenMesh/Core/*.h*",
        "src/OpenMesh/Core/Geometry/*.h*",
        "src/OpenMesh/Core/IO/*.h*",
        "src/OpenMesh/Core/IO/exporter/*.h*",
        "src/OpenMesh/Core/IO/importer/*.h*",
        "src/OpenMesh/Core/IO/reader/*.h*",
        "src/OpenMesh/Core/IO/writer/*.h*",
        "src/OpenMesh/Core/Mesh/*.h*",
        "src/OpenMesh/Core/Mesh/gen/*.h*",
        "src/OpenMesh/Core/System/*.h*",
        "src/OpenMesh/Core/Templates/*.h*",
        "src/OpenMesh/Core/Utils/*.h*",
        "src/OpenMesh/Tools/*.h*",
        "src/OpenMesh/Tools/Decimater/*.h*",
        "src/OpenMesh/Tools/Dualizer/*.h*",
        "src/OpenMesh/Tools/HoleFiller/*.h*",
        "src/OpenMesh/Tools/Kernel_OSG/*.h*",
        "src/OpenMesh/Tools/SmartTagger/*.h*",
        "src/OpenMesh/Tools/Smoother/*.h*",
        "src/OpenMesh/Tools/Subdivider/*.h*",
        "src/OpenMesh/Tools/Subdivider/Adaptive/*.h*",
        "src/OpenMesh/Tools/Subdivider/Adaptive/Composite/*.h*",
        "src/OpenMesh/Tools/Subdivider/Uniform/*.h*",
        "src/OpenMesh/Tools/Subdivider/Uniform/Composite/*.h*",
        "src/OpenMesh/Tools/Utils/*.h*",
        "src/OpenMesh/Tools/VDPM/*.h*",
        "src/OpenMesh/Tools/VDPM/xpm/*.h*",

        -- c sources (kept if you actually have .c files)
        "src/OpenMesh/*.c",
        "src/OpenMesh/Core/*.c",
        "src/OpenMesh/Core/Geometry/*.c",
        "src/OpenMesh/Core/IO/*.c",
        "src/OpenMesh/Core/IO/exporter/*.c",
        "src/OpenMesh/Core/IO/importer/*.c",
        "src/OpenMesh/Core/IO/reader/*.c",
        "src/OpenMesh/Core/IO/writer/*.c",
        "src/OpenMesh/Core/Mesh/*.c",
        "src/OpenMesh/Core/Mesh/gen/*.c",
        "src/OpenMesh/Core/System/*.c",
        "src/OpenMesh/Core/Templates/*.c",
        "src/OpenMesh/Core/Utils/*.c",
        "src/OpenMesh/Tools/*.c",
        "src/OpenMesh/Tools/Decimater/*.c",
        "src/OpenMesh/Tools/Dualizer/*.c",
        "src/OpenMesh/Tools/HoleFiller/*.c",
        "src/OpenMesh/Tools/Kernel_OSG/*.c",
        "src/OpenMesh/Tools/SmartTagger/*.c",
        "src/OpenMesh/Tools/Smoother/*.c",
        "src/OpenMesh/Tools/Subdivider/*.c",
        "src/OpenMesh/Tools/Subdivider/Adaptive/*.c",
        "src/OpenMesh/Tools/Subdivider/Adaptive/Composite/*.c",
        "src/OpenMesh/Tools/Subdivider/Uniform/*.c",
        "src/OpenMesh/Tools/Subdivider/Uniform/Composite/*.c",
        "src/OpenMesh/Tools/Utils/*.c",
        "src/OpenMesh/Tools/VDPM/*.c",
        "src/OpenMesh/Tools/VDPM/xpm/*.c",

        -- cc sources
        "src/OpenMesh/*.cc",
        "src/OpenMesh/Core/*.cc",
        "src/OpenMesh/Core/Geometry/*.cc",
        "src/OpenMesh/Core/IO/*.cc",
        "src/OpenMesh/Core/IO/exporter/*.cc",
        "src/OpenMesh/Core/IO/importer/*.cc",
        "src/OpenMesh/Core/IO/reader/*.cc",
        "src/OpenMesh/Core/IO/writer/*.cc",
        "src/OpenMesh/Core/Mesh/*.cc",
        "src/OpenMesh/Core/Mesh/gen/*.cc",
        "src/OpenMesh/Core/System/*.cc",
        "src/OpenMesh/Core/Templates/*.cc",
        "src/OpenMesh/Core/Utils/*.cc",
        "src/OpenMesh/Tools/*.cc",
        "src/OpenMesh/Tools/Decimater/*.cc",
        "src/OpenMesh/Tools/Dualizer/*.cc",
        "src/OpenMesh/Tools/HoleFiller/*.cc",
        "src/OpenMesh/Tools/Kernel_OSG/*.cc",
        "src/OpenMesh/Tools/SmartTagger/*.cc",
        "src/OpenMesh/Tools/Smoother/*.cc",
        "src/OpenMesh/Tools/Subdivider/*.cc",
        "src/OpenMesh/Tools/Subdivider/Adaptive/*.cc",
        "src/OpenMesh/Tools/Subdivider/Adaptive/Composite/*.cc",
        "src/OpenMesh/Tools/Subdivider/Uniform/*.cc",
        "src/OpenMesh/Tools/Subdivider/Uniform/Composite/*.cc",
        "src/OpenMesh/Tools/Utils/*.cc",
        "src/OpenMesh/Tools/VDPM/*.cc",
        "src/OpenMesh/Tools/VDPM/xpm/*.cc"    -- removed stray comma inside the string here
    }

    includedirs {
		"src",
        "src/OpenMesh",
        "src/OpenMesh/Core",
        "src/OpenMesh/Core/Geometry",
        "src/OpenMesh/Core/IO",
        "src/OpenMesh/Core/IO/exporter",
        "src/OpenMesh/Core/IO/importer",
        "src/OpenMesh/Core/IO/reader",
        "src/OpenMesh/Core/IO/writer",
        "src/OpenMesh/Core/Mesh",
        "src/OpenMesh/Core/Mesh/gen",
        "src/OpenMesh/Core/System",
        "src/OpenMesh/Core/Templates",
        "src/OpenMesh/Core/Utils",
        "src/OpenMesh/Tools",
        "src/OpenMesh/Tools/Decimater",
        "src/OpenMesh/Tools/Dualizer",
        "src/OpenMesh/Tools/HoleFiller",
        "src/OpenMesh/Tools/Kernel_OSG",
        "src/OpenMesh/Tools/SmartTagger",
        "src/OpenMesh/Tools/Smoother",
        "src/OpenMesh/Tools/Subdivider",
        "src/OpenMesh/Tools/Subdivider/Adaptive",
        "src/OpenMesh/Tools/Subdivider/Adaptive/Composite",
        "src/OpenMesh/Tools/Subdivider/Uniform",
        "src/OpenMesh/Tools/Subdivider/Uniform/Composite",
        "src/OpenMesh/Tools/Utils",
        "src/OpenMesh/Tools/VDPM",
        "src/OpenMesh/Tools/VDPM/xpm",
    }
    --[[ 
        ***IMPORTANT!!!!***
        Never, ever put any thing global after filters, LUA is not python and indentations doesn't tell the script anything
        as soon as you put anything after the filter, it will be a part of that filter, taking the below line under filters,
        will hide them and the compilation might fail depending on the filter type 
    ]]

    -- linux specifics
    filter "system:linux"
        pic "On"
        staticruntime "On"
        systemversion "latest"
        defines { "_GLFW_X11", "GLFW_EXPOSE_NATIVE_X11" }
         buildoptions {
         "-Wall",
         "-Wextra",
         "-Wconversion",
         "-Wfloat-conversion",
       ---  "-Werror",
         "-fPIC",
         "-ggdb",
         "-fdiagnostics-color=auto",
         "-finput-charset=UTF-8",
         "-fexec-charset=UTF-8"
      }


    filter {}
    -- windows specifics
    filter "system:windows"
        staticruntime "On"
        systemversion "latest"
        buildoptions {  "/external:W0", "/utf-8" } 

        defines
        {
            "_USE_MATH_DEFINES",
            "WIN32","_WIN32",
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }
        buildoptions { "/bigobj" }
        
    filter "configurations:Debug"
        runtime "Debug"
        targetsuffix "d"
        symbols "on"
    filter {}
    filter "configurations:Release"
        runtime "Release"
        optimize "on"
    filter {}
filter {}