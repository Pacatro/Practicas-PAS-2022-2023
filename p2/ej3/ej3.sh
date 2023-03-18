#! /bin/bash
count(){
    for word in $file; do
        grep -o -i $word $file
    done
}

if [ $# != 1 ]; then
    echo -e "Argumentos incorrectos.\nUso: ./ejercicio3.sh <fichero>"
    exit
fi

file=$1

echo -e "#\tCount\t\tWord"

echo -e "$(count)$(grep -wo '[[:alpha:]]*' $file | sort -u | tr '[:upper:]' '[:lower:]' | uniq)" > words

nl words
rm words