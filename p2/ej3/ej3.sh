#! /bin/bash
if [ $# != 1 ]; then
    echo -e "Argumentos incorrectos.\nUso: ./ejercicio3.sh <fichero>"
    exit
fi

file=$1

echo -e "#\tCount\t\tWord"
grep -wo '[[:alpha:]]*' $file | sort -u | tr '[:upper:]' '[:lower:]' | uniq > file
nl file
rm file