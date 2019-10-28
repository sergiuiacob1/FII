#!/bin/bash

let n=$1

function rec(){
	if [ $1 -le 1 ]
	then
		echo $1
	else
		echo $(( 3*$(rec $[$1-1]) - 2*$rec($[$1-2]) ))
	fi
}

rec $1
