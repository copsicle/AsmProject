@echo off
echo Warning! This will overwrite all your changes!
pause
git fetch --all
git reset --hard origin/master
git pull origin master
pause