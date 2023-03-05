#!/bin/bash
listarFicheros(){
    for files in $(find $dir -type f -name "*.$ext"); do
        echo -e "$(basename $files)\t$(grep -o '.' $files | wc -l)\t$(grep -o $char $files | wc -l)" >> files.txt  
    done
}

if [ $# != 2 ]; then
    echo -e "Argumentos incorrectos.\nUso: ./ejercicio4.sh <ruta_directorio> <extension_fichero>"
fi

dir=$1
ext=$2

echo -e "Caracter a contar: "
read char

echo -e "\nFicheros:"
listarFicheros $char
nl files.txt
rm files.txt
