project "Starlight"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("Binaries/" .. outputdir)
    objdir ("Intermediate/" .. outputdir)

    files 
    {
        "Source/**.cpp",
        "Source/**.h"
    }

    includedirs
    {
        "Source",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.msdf_atlas_gen}",
        "%{IncludeDir.msdfgen}"
    }

    links
    {
        "GLFW",
        "Glad",
        "msdf-atlas-gen"
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