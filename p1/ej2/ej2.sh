#!/bin/bash
if [ $# == 0 ]; then
    echo "Argumentos incorrectos. Uso: ./ej2.sh <ruta_directorio>"
    exit
fi

ruta_dir=$1
chmod u+rwx,g+x,o-rwx $ruta_dir   
cd $ruta_dir

echo -e "Cambiando permisos directorios: $ruta_dir"

for dirs in $(ls); do
    echo -e "\nCambiando permisos directorios: $dirs\n"
    chmod u+rwx,g+x,o-rwx $dirs
    cd $dirs

    for files_sh in $(find -name "*.sh"); do
        echo -e "Cambiando permisos directorios .sh: $files_sh"
        chmod u+x $files_sh
    done

    for files_key in $(find -name "*.key"); do
        echo -e "Cambiando permisos directorios .key: $files_key"
        chmod u+rwx,g-rwx,o-rwx $files_key
    done

    cd ..
done

#TODO: Terminar parte users
for users in $(who); do
    echo $users
done