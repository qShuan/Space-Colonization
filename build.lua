workspace "Space Colonization"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "SpaceColonization"

project "SpaceColonization"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    staticruntime "Off"
    targetdir "bin/%{cfg.architecture}/%{cfg.buildcfg}"
    objdir    "obj/%{cfg.architecture}/%{cfg.buildcfg}"
    flags { "MultiProcessorCompile" }

    files {
        "src/**.cpp",
        "src/**.h",
        "include/**.cpp",
        "include/**.hpp",
        "include/**.h"
    }

    includedirs {
        "src",
        "include",
        "include/utils",
        "include/imgui",
        "include/imgui-styles"
    }

    libdirs {
        "lib"
    }

    defines {
        "SFML_STATIC"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        links {
            "sfml-system-s-d",
            "sfml-window-s-d",
            "sfml-graphics-s-d",
            "opengl32",
            "winmm"
        }
        defines{
            "_DEBUG",
            "_CONSOLE"
        }

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
        links {
            "sfml-system-s",
            "sfml-window-s",
            "sfml-graphics-s",
            "opengl32",
            "winmm"
        }
        defines{
            "NDEBUG",
            "_CONSOLE"
        }