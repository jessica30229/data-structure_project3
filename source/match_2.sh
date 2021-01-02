#!/bin/bash
# Program:
# 算勝率
# History:
# 2020/01/02
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

calc(){ awk "BEGIN { print $* }"; }
# add this as a separate script and make it available in $PATH so you will always have it in your local shell

echo "Compiling"
g++ chain_reaction.cpp board.cpp rules.cpp player.cpp algorithm_ST.cpp algorithm_TA.cpp

export red=0
export blue=0
export numofgame=30
export max=4

for ((i = 0 ; i < $numofgame ; i++)); do
    out=`./a.out > output`
    final=`cat output | grep "Blue Player won"`
    final2=`cat output | grep "Red_Player violated the game rules."`
    #echo $final2
    if [ "$final2" != "" ]; then
        echo "red player violated"
        exit
    fi
    if [ "$final" == "" ]; then
        echo "red won"
        red=$((red+1))
        if [ "$red" == "$max" ]; then
            echo "red win!"
            exit
        fi
    else
        echo "blue won"
        blue=$((blue+1))
        if [ "$blue" == "$max" ]; then
            echo "blue win!"
            exit
        fi
    fi
done

echo "$numofgame games"
echo "Red wins $red $(calc $red / $numofgame)"
echo "Blue wins $blue $(calc $blue / $numofgame)"