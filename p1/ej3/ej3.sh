#!/bin/bash
deleteFiles(){
    for files in $(ls); do
        file_time=$(stat -c %Y "$files")
        current_time=$(date +%s)
        time_diff=$((current_time - file_time))

        if [ $time_diff -gt 200 ]; then
            rm $files
            echo "Copias antiguas borradas."
        fi
    done
}

if [ $# == 0 ]; then
    echo -e "Argumentos incorrectos\nUso: ./eje3.sh <dir_origen (!/)> <dir_destino>"
    exit
fi

dir_destino=$2
dir_origen=$(basename $1)
nombre_copia=$dir_origen"_"$USER"_"$(date +%s)".tar.gz"

if !([ -d $dir_destino ]); then
    mkdir $dir_destino
fi

#TODO: HACER OTRA CARPETA DENTRO DE COPIA Y GUARDAR
        #LOS COMPRIMIDOS AHI

cd $dir_destino
tar cvzf $nombre_copia "../"$dir_origen > /dev/null
echo -e "\nCopia realizada en $dir_destino/$nombre_copia"

if ls; then
        echo $(deleteFiles)
    else
        exit
fi

