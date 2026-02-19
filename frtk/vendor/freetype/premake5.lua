project "freetype"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir ("../../../bin/")
    objdir ("../../../bin_obj/")
    

     files
    {
        --- Mandatory FreeType source files ---
        "src/base/*.c",        
        "src/bdf/*.c",         
        "src/sdf/*.c",                 
        "src/cache/*.c",       
        "src/cff/*.c",         
        "src/cid/*.c",         
        "src/dlg/*.c",         
        "src/pcf/*.c",         
        "src/pfr/*.c",         
        "src/psaux/*.c",       
        "src/psnames/*.c",     
        "src/raster/ftraster.c",  
        "src/raster/raster.c",  
        "src/sfnt/*.c",        
        "src/smooth/ftsmooth.c",
        "src/smooth/ftgrays.c",
        "src/svg/*.c",         
        "src/truetype/*.c",    
        "src/type1/*.c",       
        "src/type42/*.c",      
        "src/winfonts/*.c",    

        --- Optional modules (enable if needed) ---
         "src/autofit/*.c",   
        "src/pshinter/*.c",   
        --"src/gxvalid/*.c",  
        --"src/otvalid/*.c",  
        --"src/bzip2/*.c",    
        --"src/gzip/*.c",     

        --- Header files ---
        --- 
        "src/base/*.h",
        "src/autofit/*.h",   -- auto-hinting
        "src/pshinter/*.h", -- PostScript hinting (needed for PS fonts)
        "src/bdf/*.h",
        "src/sdf/*.h",
        "src/cache/*.h",
        "src/cff/*.h",
        "src/cid/*.h",
        "src/dlg/*.h",
        "src/pcf/*.h",
        "src/pfr/*.h",
        "src/psaux/*.h",
        "src/psnames/*.h",
        "src/raster/ftraster.h",
        "src/raster/rasterrs.h",
        "src/raster/ftmisc.h",
        "src/sfnt/*.h",
        "src/smooth/ftsmooth.h",
        "src/smooth/ftgrays.h",
        "src/svg/*.h",
        "src/truetype/*.h",
        "src/type1/*.h",
        "src/type42/*.h",
        "src/winfonts/*.h",
        "include/**"
    }



    includedirs
    {
        "include",
        "include/freetype",
        "include/freetype/config"
    }

    defines {
        "FT2_BUILD_LIBRARY",

        -- Fully disable all optional compression
        "FT_CONFIG_OPTION_DISABLE_ZLIB",
        "FT_CONFIG_OPTION_DISABLE_LZW",
        "FT_CONFIG_OPTION_DISABLE_BZIP2",

        "_LIB",
        "_CRT_SECURE_NO_WARNINGS",
        "FT_DEBUG_LEVEL_ERROR",
        "FT_DEBUG_LEVEL_TRACE",
    }

    filter "system:linux"
        pic "On"
        staticruntime "On"
        systemversion "latest"
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
    
    filter "system:windows"
        defines { "WIN32", "_DEBUG" }
        systemversion "latest"
        buildoptions {  "/external:W0", "/utf-8" }
        
    filter "configurations:Debug"
        runtime "Debug"
        targetsuffix "d"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
    filter {}