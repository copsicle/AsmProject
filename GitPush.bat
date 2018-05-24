git add *.inc
git add *.asm
git add *.bat
git add *.bmp
git status
pause
SET /P commie= "Enter commit comment : "
git commit -m "%commie%"
git push -u origin master
pause