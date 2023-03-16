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
echo -e "$(cat $fich | grep -o '\-.*\-')\n"

echo -e "3) Hay $(cat $fich | grep -o -c '2016') películas de 2016 y $(cat $fich | grep -o -c '2017') del 2017\n  "

echo -e "4) Palabras que contengan d, l o t , una vocal , y misma letra"
echo -e "$(cat $fich | grep -Eo '[a-zA-Z]*([dlt])[aeiou]\1[a-zA-Z]*')"

echo -e "\n5) Lineas que acaben con 3 puntos y no empiecen por espacios\n"
echo -e "$(cat peliculas.txt | grep  '^[^ ].*\.\{3,3\}')\n"
echo -e "6) Mostrar las vocales mayusculas o minusculas que tengan tildes entre comillas\n"
echo -e "$(cat peliculas.txt | sed -r -e 's/[áéíóúÁÉÍÓÚ]/" "/g')"