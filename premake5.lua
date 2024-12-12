-- premake5.lua
workspace "logger"
   configurations { "Debug", "Release" }
   location "build"

project "logger"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"
   
   targetdir "build/%{cfg.buildcfg}"
   includedirs { "../utils/src"}

   files { "src/**.hpp", "src/**.cpp" }

   filter "configurations:Debug"
	  architecture "x86_64"  	  
	  defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      architecture "x86_64"     
	  defines { "NDEBUG" }
      optimize "Speed"