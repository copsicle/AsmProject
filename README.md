# The Amazing Assembly Project
Welcome to the project page.
I really don't know what I want my project to be yet but it needs to be something cool or a basic game.
This is on assembly 32 using LibDRD which is a "window manager" for assembly, LibDRD is on GitHub if you want the source code.
Also in this project I'm not allowed to use .if and other high level stuff.

# Requirements
The assembler is MASM32 which you can [here](http://www.masm32.com/download.htm).
I build the code on Visual Studio 2017, I also recommend downloading the AsmDude add-on.
LibDRD is in this project (drd.inc & drd.lib) but if you want the source code you  can get that [here](https://github.com/shooshx/libDRD).
You also need git for the git scripts (duh).
To make sure that you build this successfully in Visual Studio you have to do the following:
1. Create a new empty C++ project.
2. Right click the project in the Solution Explorer -> Build Dependencies -> Build Customization's... -> Put a tick on MASM -> OK (If you don't have MASM as an option you might've installed MASM incorrectly [or not at all]).
3. Right click the project again -> Properties -> Linker -> System -> SubSystem -> Windows -> Press Apply and OK.
4. Right click the project yet again -> Open Folder In File Explorer -> Either download and drop all the files directly or just create a new git repo in this dir and pull from github.
5. Drag all the files onto the project name in the solution explorer, all of them should be added to the solution.
6. On the top toolbar click Build -> Rebuild Solution and run (Local Windows Debugger).

# License
If you really searched deep in GitHub to find this specific project and you want to copy it (like one very specific person which may or may not be reading this) sure, I won't stop you (or will I?).
