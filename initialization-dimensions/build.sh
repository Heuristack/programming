#!/bin/bash

LH=(NL RL CL)
RH=(0 1 2 P)

function build()
{
    for ((i=0; i<${#RH[@]}; i=i+1)); do
        command="clang++ main.cpp "
        options="-std=c++1z -D${1}${RH[i]} "
        for ((j=0; j<${#LH[@]}; j=j+1)); do
            options+="-D${LH[j]}${RH[i]} ";
        done
        command=${command}${options}
        echo $command
        eval $command &> ${1}-${RH[i]}.txt
    done
}

build EC
build IC

