# About

This a simple 3D graphics program to demonstrate some of the capabilities of OpenGL.
It is written in C, using the Win32, OpenGL and GLEW APIs.
It uses custom shaders written in GLSL to achieve effects such as normal mapping.

# Usage

* Mouse to look around
* `W` forward
* `A` left
* `S` backward
* `D` right
* `C` crouch
* `SPACE` jump

# Building

The following dependencies are required in order to build this project:
* Windows
* OpenGL version >= 4.4
* GLEW version >= 1.10

If you are using Visual Studio, import all C source and header files into your solution, and follow these steps:
* Set your solution platform to Win32
* Follow the installation instructions for [GLEW](http://glew.sourceforge.net/install.html). To summarize, download the windows binaries, extract the archive, copy the following with administrator priviledges:
    * `bin\Release\Win32\glew32.dll` to `VC\bin`
    * `lib\Release\Win32\glew32.lib` to `VC\lib`
    * `include\GL\glew.h` to `VC\include\GL`
    * `include\GL\wglew.h` to `VC\include\GL`
* Add as additional library dependencies to the linker: `opengl32.lib`, `glu32.lib`, `glew32.lib`.

# License

This project is distributed under the MIT license.
