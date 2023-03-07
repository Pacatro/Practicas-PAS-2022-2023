#!/bin/bash
listarFicheros(){
    for files in $(find $dir -type f -name "*.$ext"); do
        echo -e "\t$(basename $files)\t\t$(grep -o '.' $files | wc -l)\t\t$(grep -o $char $files | wc -l)" >> files.txt  
    done

    nl files.txt
    rm files.txt
}

if [ $# != 2 ]; then
    echo -e "Argumentos incorrectos.\nUso: ./ejercicio4.sh <ruta_directorio> <extension_fichero>"
    exit
fi

dir=$1
ext=$2

echo -e "Caracter a contar: "
read char

echo -e "\nFicheros:"
listarFicheros $char
