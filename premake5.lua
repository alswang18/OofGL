include "dependencies/conandeps.premake5.lua"

workspace "OofEngine"
    configurations { "Debug", "Release" }
    architecture "x64"

    project "OofEngineApp"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"

        targetdir   "build/%{cfg.buildcfg}/bin"
        objdir      "build/%{cfg.buildcfg}/obj"

        location "./src"
        files { "%{prj.location}/**.h", "%{prj.location}/**.cpp" }

        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"
        filter {}

        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"
        filter {}

        conan_setup()
        linkoptions { "/IGNORE:4099" }