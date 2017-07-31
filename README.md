# Basic-OpenGL-Modules

This is a small libary with diffrent modules for building games and other media application using OpenGL.

All libarys in the libary folder are 64Bit if you want to use the Basic-OpenGL-Modules you have to replace them with the 32 Bit ones.
The following libarys will be found in the libary folder.

* SDL2 for OpenGL initalisation and inputhandling
* SDL_mixer for sounds
* SDL_image for advanced texture formats like png.
* glm for the advanced support.

The libary also provides base classes for the 
[Entity-Component Pattern](http://gameprogrammingpatterns.com/component.html)

You have to compile the libary yourself there is no CMakefile atm
This is because the libary isen't finished yet and i provide some example code (main.cpp).
But i will provide the dlls son

## Installation

### Windows 
* Download Visual Studio 2015
* Clone the repository
* (optional) If you using a 32Bit system swap out the libarys for 32 bit
* Load the soulution file into Visual Studio.
* Run

### Linux 
* Use a IDE of your choise 
* Load everything into your project.
* Set those paths as additional include paths
  - .\src\libarys\includes
  - .\src
* (optional) If you using a 32Bit system swap out the libarys for 32 bit
* use the following linkers in your dependency list
  - glew32.lib
  - glew32s.lib
  - SDL2.lib
  - SDL2main.lib
  - SDL2_image.lib
  - SDL2_mixer.lib
  - OpenGL32.lib(maybe diffrent under linux)


## So far covert:
* OpenGL Window
* Textures
* Basic camera component(needs to be improved)
* VBO Renderer
* PLY Parser ( PLY format can be exported by blender)
* Shaders
* Png Loading

## In Progress

* Lightning
* Partikel
* Highmap Terrain generation

