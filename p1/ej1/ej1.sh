#!/bin/bash
if [ $# == 0 ]; then
    echo "Wrong input"
    exit
fi

randName(){
    let length=($RANDOM%max+1)+min
    echo `tr -dc A-Za-z0-9 < /dev/urandom | head -c $length`
}

ruta_dir=$1
let n_dir=$2
let min=$3
let max=$4

if [ -d $ruta_dir ]; then
    echo "La ruta específica ya existe, ¿eliminar? (Si: Y | No: N)"
    read -t5 option

    if [ $option == "Y" ] || [ $option == "y" ]; then
        echo `rm -r $ruta_dir`
        echo "Directorio borrado"
    else
        echo "El directorio no se ha borrado"
    fi
fi

mkdir $ruta_dir
cd $ruta_dir

for i in $(seq $n_dir); do
    dir_name=$(randName)
    mkdir $dir_name
    cd $dir_name

    touch $(randName).key
    touch $(randName).sh
    touch $(randName).txt
    touch $(randName).html

    cd ..
done

echo "Directorios creados"