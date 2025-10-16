project "freetype"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir ("../../../bin/")
    objdir ("../../../bin_obj/")

    files
    {
		---source 
		"src/autofit/*.c",
		"src/base/*.c",
		"src/bdf/*.c",
		"src/bzip2/*.c",
		"src/cache/*.c",
		"src/cff/*.c",
		"src/cid/*.c",
		"src/dlg/*.c",
		"src/gxvalid/*.c",
		---"src/gzip/*.c",
		"src/otvalid/*.c",
		"src/pcf/*.c",
		"src/pfr/*.c",
		"src/psaux/*.c",
		"src/pshinter/*.c",
		"src/psnames/*.c",
		"src/raster/*.c",
		"src/sdf/*.c",
		"src/sfnt/*.c",
		"src/smooth/*.c",
		"src/svg/*.c",
		"src/truetype/*.c",
		"src/type1/*.c",
		"src/type42/*.c",
		"src/winfonts/*.c",
		---headers		
		"src/autofit/*.h",
		"src/base/*.h",
		"src/bdf/*.h",
		"src/bzip2/*.h",
		"src/cache/*.h",
		"src/cff/*.h",
		"src/cid/*.h",
		"src/dlg/*.h",
		"src/gxvalid/*.h",
		---"src/gzip/*.h",
		"src/otvalid/*.h",
		"src/pcf/*.h",
		"src/pfr/*.h",
		"src/psaux/*.h",
		"src/pshinter/*.h",
		"src/psnames/*.h",
		"src/raster/*.h",
		"src/sdf/*.h",
		"src/sfnt/*.h",
		"src/smooth/*.h",
		"src/svg/*.h",
		"src/truetype/*.h",
		"src/type1/*.h",
		"src/type42/*.h",
		"src/winfonts/*.h"	

		--- Excluded folders
	--[[     "src/lzw/*.c",
             "src/lzw/*.h},
		    "src/tools/*.c",
            "src/tools/*.h]]

    }

    --[[ 
        ***IMPORTANT!!!!***
        Never, ever put any thing global after filters, LUA is not python and indentations doesn't tell the script anything
        as soon as you put anything after the filter, it will be a part of that filter, taking the below line under filters,
        will hide them and the compilation might fail depending on the filter type 
    ]]

    includedirs
    {
        "include/"
    }

    defines
    {
        "_LIB",
        "_CRT_SECURE_NO_WARNINGS",
        "FT_DEBUG_LEVEL_ERROR",
        "FT_DEBUG_LEVEL_TRACE",
        "FT2_BUILD_LIBRARY",
        "DLL_EXPORT"
    }
    
    -- buildoptions {
    --     "FT_DISABLE_ZLIB",
    --     "FT_DISABLE_BZIP2",
    --     "FT_DISABLE_PNG",
    --     "FT_DISABLE_HARFBUZZ",
    --     "FT_DISABLE_BROTLI"
    -- }
    
    filter "system:linux"
        pic "On"
        staticruntime "On"
        systemversion "latest"
        buildoptions { "-Wall", "-Wextra", "-fPIC", "-fdiagnostics-color=auto" }
        filter "configurations:Debug"
            buildoptions { "-ggdb" } 

    filter "system:windows"
        defines
        {
            "WIN32",
            "_DEBUG"
        }
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        targetsuffix "d"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"