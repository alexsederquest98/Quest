outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to the root (solution)
IncludeDir = {}
IncludeDir["glfw"] = "Quasar/vendor/glfw/include"
IncludeDir["imgui"] = "Quasar/vendor/imgui/"
IncludeDir["glm"] = "Quasar/vendor/glm"
IncludeDir["spdlog"] = "Quasar/vendor/spdlog/include"

workspace "QuasarEngine"
    architecture "x64"
    startproject "Sandbox"
    configurations {
        "Debug", "Release", "Distribution"
    }

-- Include premake5.lua in vendor libs
include "Quasar/vendor/glfw"

project "Quasar"
    location "Quasar"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "qspch.h"
    pchsource "Quasar/src/qspch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",

        "vendor/glm/glm/**.hpp",
        "vendor/glm/glm/**.inl"
    }

    includedirs {
        "%{prj.name}/src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.imgui}",
        "$(VULKAN_SDK)/Include"
    }

    links {
        "glfw",
        "$(VULKAN_SDK)/Lib/vulkan-1.lib"
    }

    -- Having an issue with this define it seems
    defines {
        "QS_ENABLE_ASSERTS"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "QS_PLATFORM_WINDOWS"
        }

        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "QS_DEBUG"
        buildoptions "/MDd"
        symbols "On"
        defines {
            "QS_ENABLE_ASSERTS"
        }

    filter "configurations:Release"
        defines "QS_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Distribution"
        defines "QS_DIST"
        buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Quasar/src",
        "Quasar/vendor/spdlog/include",
        "Quasar/vendor/",
        "Quasar/vendor/glfw/include",
        "Quasar/vendor/glm"
    }

    links {
        "Quasar"
    }

    filter "system:windows"
        systemversion "latest"

        defines {
            "QS_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "QS_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "QS_RELEASE"
        optimize "On"

    filter "configurations:Distribution"
        defines "QS_DIST"
        optimize "On"