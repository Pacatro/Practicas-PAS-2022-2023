#!/bin/bash
listarFicheros(){
    for files in $(find $dir -type f -name "*.$ext"); do
        name=$(basename $files)
        echo $name > nomfile
        echo -e "\t$(basename $files)\t\t${#name}\t\t$(grep -o $char nomfile | wc -l)" >> files.txt 
    done

    nl files.txt
    rm files.txt
    rm nomfile
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
