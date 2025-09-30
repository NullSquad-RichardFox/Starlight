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

group "Dependencies"
    include "Starlight/ThirdParty/GLFW/GLFW.lua"
    include "Starlight/ThirdParty/Glad/Glad.lua"
group ""

group "Starlight"
    include "Sandbox/Sandbox.lua"
    include "Starlight/Starlight.lua"
group ""