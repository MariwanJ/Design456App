# Design456App
Turn Design456 Workbench to more powerful software

# Notes:
This is an expermental pieces of code. Please don't use it in any serious application. 
It is still in very earliy development stage and I need more time to make it useful. 
Only Windows is supported. Glad is not the latest. My laptop dosen't support that. 

# Status:
1-GLFW window is embedded to FLTK. But refereshing / repainint is not working well. FLTK dosen't update the embedded system as it should. Why? I don't know yet :(

2-Some issues with the LOG system. 

3-Code might change alot. So be patient

4-You need to download FLTK and compile it by yourself. It should be under frtk/vendor/fltk folder. 

5-Since I am submoduling some libraries, lua files are not included with these submodules. At the moment I don't know how to get that fixed. You find the files under the folder Resources for each module.

Don't forget that you need to download preemake5.exe 

# Some Ideas are comming from:
Some of the code is inspired by TheCherno and Hazel Game Engine. 
