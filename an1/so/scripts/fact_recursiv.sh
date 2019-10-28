#!/bin/bash

let n=$1

function fact(){
	if [ $1 -lt 2 ] 
	then
		echo 1
	else
		echo $[ $1 * $(fact $[$1-1]) ]
	fi
}

fact $n
