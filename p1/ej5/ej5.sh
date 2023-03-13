#!/bin/bash
listar(){
    echo -e "Nombre; Fecha creación; Tamaño; Permisos; Ejecutable:\n"
    for file in $(find $dir -size "+"$tam_bytes"c" | sort -t":" -k3n); do
        if !([ -d $file ]); then
            name=$(basename $file)
            fecha=$(stat -c %w $file)
            bytes=$(stat -c %s $file)
            permisos=$(echo $(ls -la $file) | cut -d ' ' -f1)
            
            let esX=0
            if [ -x $file ]; then
                esX=1
            fi

            echo -e "$name; $fecha; $bytes; $permisos; $esX\n" >> file
            cat file | sort -t";" -k3n
            rm file
        fi
    done
}

if [ $# != 2 ]; then
    echo -e "Argumentos incorrectos.\nUso: ./ejercicio5.sh <ruta_directorio> <tam_bytes>"
    exit
fi

dir=$1
let tam_bytes=$2
listar
