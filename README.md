# Design456App

**WIP (Work In Progress)!!**

Turn the Design456 Workbench into a more powerful software application by combining GLFW, ImGui, and ImGuizmo into one application that run under FreeCAD.

## Notes
This is an experimental piece of code. Please don't use it in any serious application. It is still in a very early development phase, and I need more time to make it useful.

**Only Windows is supported at the moment. Glad is version 4.x.**

## Status
- New GUI toolkit is designed based on NanoVG library WIP. 
- Issues with ImGui; the Windows GUI is not fully functional yet.
- Support for Linux is almost there, it compiles but has some bugs which doesn't happen in Windows. :( 
- Code optimization specially events processing.
- Compilation in Linux due to the library creating is somehow slow. I will look at that later. 
- I know that FLTK and GLFW are not a good combination. I tried some code, which you fin in the frozen version/branch, but that was the end of my efforts with fltk approach.

**Please ensure you download `premake5`.**

## Acknowledgments
- This project started by modifying the https://github.com/gligneul/Scene-Graph. Thanks go to Gabriel de Quadros Ligneul (gligneul)
- Some of the code is inspired by TheCherno and the Hazel Game Engine. Thanks!


-------------------------------------------------
![Screenshot](screenshot.png)
