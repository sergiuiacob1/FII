#!/bin/bash

if [ $# -eq 0 ]
then
	read n
else
	let n=$1
fi

function fib(){
	if [ $1 -lt 2 ]
	then
		echo $1
	else
		echo $(( $(fib $[$1-1]) + $(fib $[$1-2] ) ))
	fi
}


fib $n
