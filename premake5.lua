include "./vendor/premake/premake_customization/solution_items.lua"

workspace "BlockCraft"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}

IncludeDir["Glad"] = "%{wks.location}/vendor/Glad/include"
IncludeDir["glcore"] = "%{wks.location}/vendor/glcore"
IncludeDir["GLFW"] = "%{wks.location}/vendor/GLFW/include"
IncludeDir["ImGui"] = "%{wks.location}/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/vendor/stb_image"

group "Dependencies"
	include "vendor/GLFW"
	include "vendor/Glad"
	include "vendor/imgui"
	include "vendor/glcore"
group ""
project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"%{wks.location}/vendor/stb_image/**.h",
		"%{wks.location}/vendor/stb_image/**.cpp",
		"%{wks.location}/vendor/glm/glm/**.hpp",
		"%{wks.location}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.glcore}",
	}

	links
	{
		"Glad",
		"glcore",
		"GLFW",
		"ImGui",
		"opengl32.lib"
	}
	defines{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "FIKO_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FIKO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "FIKO_DIST"
		runtime "Release"
		optimize "on"

