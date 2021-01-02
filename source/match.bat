@echo off
g++ chain_reaction.cpp board.cpp rules.cpp player.cpp algorithm_ST.cpp algorithm_TA.cpp
set /a red=0
set /a blue=0
set /a numofgame=30
IF NOT (%1)==() (set /a numofgame=%1)
for /L %%n in (1 1 %numofgame%) do (
@REM for /L %%n in (1 1 30) do (
a.exe > output
find "Red Player won the game" .\output>nul && set /a red+=1
find "Blue Player won the game" .\output>nul && set /a blue+=1
)
echo  %numofgame% games
echo Red wins %red%
echo Blue wins %blue%
del .\output
del .\a.exe
@REM pause