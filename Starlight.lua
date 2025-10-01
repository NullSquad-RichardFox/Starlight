workspace "Starlight"
    architecture "x64"
    startproject "Sandbox"

    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}/%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Starlight/ThirdParty/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Starlight/ThirdParty/Glad/include"
IncludeDir["glm"] = "%{wks.location}/Starlight/ThirdParty/glm/include"
IncludeDir["stb_image"] = "%{wks.location}/Starlight/ThirdParty/stb_image/include"
IncludeDir["msdf_atlas_gen"] = "%{wks.location}/Starlight/ThirdParty/msdf-atlas-gen"
IncludeDir["msdfgen"] = "%{wks.location}/Starlight/ThirdParty/msdf-atlas-gen/msdfgen"

group "Dependencies"
    include "Starlight/ThirdParty/GLFW/GLFW.lua"
    include "Starlight/ThirdParty/Glad/Glad.lua"
    include "Starlight/ThirdParty/msdf-atlas-gen/msdf-atlas-gen.lua"
group ""

group "Starlight"
    include "Sandbox/Sandbox.lua"
    include "Starlight/Starlight.lua"
group ""