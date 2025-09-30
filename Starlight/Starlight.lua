project "Starlight"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("Binaries/" .. outputdir)
    objdir ("Intermediate/" .. outputdir)

    pchheader("pcch.h")
    pchsource("%{wks.location}/Starlight/Source/Starlight/pcch.cpp")

    files 
    {
        "Source/**.cpp",
        "Source/**.h"
    }

    includedirs
    {
        "Source",
        "Source/Starlight",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    disablewarnings
    {
        "4172"
    }

    filter "configurations:Debug"
        defines { "CF_DEBUG" }