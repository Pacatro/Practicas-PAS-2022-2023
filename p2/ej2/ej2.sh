#!/bin/bash
if [ $# != 3 ]; then
    echo -e "Argumentos erroneos.\nUso: ./ejercicio2.sh <fichero_ips> <intentos> <tiempo de espera>"
    exit
fi

file=$1
let attempts=$2
let wait_time=$3

if !([ -e $file ]); then
    echo -e "Fichero no existe"
    exit
fi

for ip in $(cat $file); do
    med=$(ping -c $attempts -W $wait_time $ip | tail -1 | grep -o '/[0-9]*\.[0-9]*/' | cut -d '/' -f 2)
    if [ -z $med ]; then
        echo -e "La IP $ip no respondio en $wait_time segundos" >> file2
    else echo -e "$ip, $med ms" >> file
    fi
done

sort -o file -k2n -u file
cat file
cat file2
rm file
rm file2