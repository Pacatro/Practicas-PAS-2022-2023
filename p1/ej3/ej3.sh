#!/bin/bash

if [ $# == 0 ]; then
    echo -e "Argumentos incorrectos\nUso: ./eje3.sh <dir_origen> <dir_destino>"
    exit
fi

dir_origen=$1
dir_destino=$2
nombre_copia=$dir_origen"_"$USER"_"$(date +%s)".tar.gz"

if echo $dir_origen | grep '/'; then
    dir_origen=${dir_origen%?}
fi

if !([ -d $dir_destino ]); then
    mkdir $dir_destino
fi

cd $dir_destino
tar cvzf $nombre_copia "../"$dir_origen