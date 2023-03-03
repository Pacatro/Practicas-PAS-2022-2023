#!/bin/bash
if [ $# != 2 ]; then
    echo "Argumentos incorrectos. Uso: ./ejercicio4.sh <ruta_directorio> <extension_fichero>"
fi

file=$(basename $1)
ext=$2

echo $file

