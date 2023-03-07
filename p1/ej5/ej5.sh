#!/bin/bash
listar(){
    cd $dir
    echo -e "Nombre; Fecha creación; Tamaño; Permisos; Ejecutable:\n"
    for file in $(ls); do
        if [ $(stat -c %s $file) -ge $tam_bytes ]; then
            name=$(basename $file)
            fecha=$(stat -c %w $file)
            bytes=$(stat -c %s $file)
            permisos=$(echo $(ls -la $file) | cut -d ' ' -f1)
            
            let esX=0
            if [ -x $file ]; then
                esX=1
            fi

            echo -e "$name; $fecha; $bytes; $permisos; $esX\n"
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
