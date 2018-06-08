@echo off
git add *.inc
git add *.asm
git add *.bat
git add *.bmp
git add *.wav
git add *.txt
git add README.md
git status
pause
SET /P commie= "Enter commit comment : "
git commit -m "%commie%"
git push -u origin master
pause