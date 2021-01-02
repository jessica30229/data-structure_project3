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
#g++ chain_reaction.cpp board.cpp rules.cpp player.cpp algorithm_ST.cpp algorithm_TA.cpp

export red=0
export blue=0
export numofgame=30

for ((i = 0 ; i < $numofgame ; i++)); do
    final=`./a.out | grep "Blue Player won"`
    # echo $final
    if [ "$final" == "" ]; then
        echo "red won"
        red=$((red+1))
    else
        echo "blue won"
        blue=$((blue+1))
    fi
done

echo "$numofgame games"
echo "Red wins $red $(calc $red / $numofgame)"
echo "Blue wins $blue $(calc $blue / $numofgame)"