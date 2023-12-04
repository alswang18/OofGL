
function includeGlad()
    includedirs "dependencies/GLAD/include"
end
-- This function includes GLFW's header files
function includeGLFW()
	includedirs "dependencies/GLFW/include"
end

function includeDependencies()
    includeGlad()
    includeGLFW()
end

-- This function links statically against GLFW
function linkGLFW()
	libdirs "dependencies/GLFW/lib"

	-- Our static lib should not link against GLFW
	filter "kind:not StaticLib"
		links "glfw3"
	filter {}
end

function linkDependencies()
    linkGLFW()
end

workspace "OpenGLOofEngine"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

project "OpenGLOofEngine"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "off"

    files { "src/*.c", "src/*.cpp" }
    
    includeDependencies()
    linkDependencies()

    filter {"system:windows"}
        links {"OpenGL32"}
        systemversion "latest"
        defines { "WINDOWS" }

    filter {"system:not windows"}
        links {"GL"}

    filter {"system:macosx"}
        defines {"MACOSX"}
    
    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        symbols "On"
        optimize "On"
    
    filter "configurations:Dist"
        defines { "DIST" }
        runtime "Release"
        symbols "Off"
        optimize "On"

    -- Reset the filter for other settings
	filter { }

	-- Here we use some "tokens" (the things between %{ ... }). They will be replaced by Premake
	-- automatically when configuring the projects.
	-- * %{prj.name} will be replaced by "ExampleLib" / "App" / "UnitTests"
	--  * %{cfg.longname} will be replaced by "Debug" or "Release" depending on the configuration
	-- The path is relative to *this* folder
	targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
	objdir ("Build/Obj/%{prj.name}/%{cfg.longname}")