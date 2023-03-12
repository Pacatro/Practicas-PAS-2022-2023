#!/bin/bash
if [ $# != 1 ]; then 
    echo -e "Argumentos erroneos.\nUso: ./ejercicio1.sh <fichero_peliculas>"
    exit
fi

fich=$1

if [ $fich != "peliculas.txt" ]; then
    echo -e "Se esperaba un fichero del tipo peliculas.txt"
    exit
fi

echo -e "1) Lineas con la duracion de las peliculas:"
echo -e "$(cat $fich | grep '^[1-9]')\n"

echo -e "2) Solo pais de las peliculas:"
echo -e "$(cat $fich | grep -o '\-[^\-]*\-')\n"

echo -e "3) Hay $(cat $fich | grep -o -c '\(/2016\)') películas de 2016 y $(cat $fich | grep -o -c '\(/2017\)') del 2017"


