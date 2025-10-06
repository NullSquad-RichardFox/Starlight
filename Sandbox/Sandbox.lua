project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("Binaries/" .. outputdir)
    objdir ("Intermediate/" .. outputdir)

    files 
    {
        "Source/**.h",
        "Source/**.cpp"
    }

    includedirs
    {
        "Source",
        "%{wks.location}/Starlight/Source",
        "%{wks.location}/Starlight/Source/Starlight",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.msdf_atlas_gen}",
        "%{IncludeDir.msdfgen}"
    }

    links 
    {
        "Starlight"
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