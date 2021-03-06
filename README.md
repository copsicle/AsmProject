# The Amazing Assembly Project
Welcome to the project page.
I'm currently focusing on making basic pong and i'll try to put a twist on the game once i'm done with the basic code.
This is on assembly 32 using LibDRD which is a "window manager" for assembly, [LibDRD is on GitHub](https://github.com/shooshx/libDRD) if you want the source code.
Also in this project I'm not allowed to use .if and other high level stuff.

# Requirements
The assembler is [MASM32](http://www.masm32.com/download.htm) and I build the code on [Visual Studio 2017](https://www.visualstudio.com/), I also recommend downloading the [AsmDude](https://marketplace.visualstudio.com/items?itemName=Henk-JanLebbink.AsmDude) add-on.
LibDRD is included in this repo (as drd.inc & drd.lib).
You also need [Git](https://git-scm.com/) for the Git scripts (duh).
To make sure that you build this successfully in Visual Studio you have to do the following:
1. Create a new empty C++ project.
2. Right click the project (notice that when I say the project I mean the second item in the Solution Explorer) -> Build Dependencies -> Build Customization's... -> Put a tick on MASM -> OK (If you don't have MASM as an option you might've installed MASM incorrectly [or not at all]).
3. Right click the project again -> Properties -> Linker -> System -> SubSystem -> Windows -> Press Apply and OK.
4. Right click the project yet again -> Open Folder In File Explorer -> Either download and drop all the files directly or just create a new git repo in this dir and pull from github.
5. Drag all the files onto the project name in the solution explorer, all of them should be added to the solution.
6. On the top toolbar click Build -> Rebuild Solution and run (Local Windows Debugger).

# Git Setup
Create a new repository on GitHub (or somewhere else it doesn't really matter as long as you have to have a link). Install Git and open CMD, input the following lines:
```git
cd C:\Users\[Username]\source\repos\[yourProject]\[yourProject]
git init
git remote add origin [yourRepoLink]
```
You should be able to use the scripts and push/pull your changes. Note that only specific file types get pushed with the script (mostly because I don't want to mess with Visual Studio's files) so you might need to modify it for your needs. Sometimes for some reason Git doesn't want to pull for the first time so if you're having this problem try running pull with the "--allow-unrelated-histories" parameter manually once and the scripts should be good from now on.

# License
If you really searched deep in GitHub to find this specific project and you want to copy it (like one very specific person who may or may not be reading this) sure, I won't stop you (or will I?).
