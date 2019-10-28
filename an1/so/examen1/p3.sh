#!/bin/bash
if [ $# -eq 0 ]
then
        echo "Introduceti n"
        read n
else
        let n=$1
fi

if [ $# -le 1 ]
then
        echo "Introduceti x"
        read x
else
        let x=$2
fi

function rec(){
        if [ $1 -eq 1 ]
        then
                echo $x
        elif [ $1 -eq 2 ]
        then
                echo 2*$x
        else
                let rez1=`rec $[ $1-1 ]`
                let rez1=rez1*rez1
                let rez2=`rec $[ $1-2 ]`
                let rez2=rez2*rez2

		echo $(( $rez1+$rez2 ))

		#echo  $(( $(rec $[ $1-1 ])*$(rec $[ $1-1 ])+$(rec $[ $1-2 ])*$(rec $[ $1-2 ]) ))
        fi
}

rec $n
