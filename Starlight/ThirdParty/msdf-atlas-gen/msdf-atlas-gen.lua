include "msdfgen/msdfgen.lua"

project "msdf-atlas-gen"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
    staticruntime "off"

    targetdir ("Binaries/" .. outputdir)
    objdir ("Intermediate/" .. outputdir)

	files
	{
		"msdf-atlas-gen/**.h",
    	"msdf-atlas-gen/**.hpp",
    	"msdf-atlas-gen/**.cpp"
	}

	includedirs
	{
		"msdf-atlas-gen",
		"msdfgen",
		"msdfgen/include"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	links
	{
		"msdfgen"
	}

	flags
    {
        "MultiProcessorCompile"
    }