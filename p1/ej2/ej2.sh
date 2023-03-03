#!/bin/bash

#Escribimos en un fichero txt los usuarios logueados sin repeticiones y los mostramos.
getUsers(){
    who > logged.txt | uniq logged.txt | who > /dev/null

    echo -e "Usuarios logueados en este momento:"
    echo $(cat logged.txt)
    rm logged.txt
}

if [ $# == 0 ]; then
    echo -e "Argumentos incorrectos.\nUso: ./ej2.sh <ruta_directorio>"
    exit
fi

ruta_dir=$1
chmod u+rwx,g+x,o-rwx $ruta_dir   
cd $ruta_dir

echo -e "Cambiando permisos directorio: $ruta_dir"

#Entramos en cada directorio para dar ir dando permisos.
for dirs in $(ls -d */); do
    echo -e "\nCambiando permisos directorio: $dirs"
    chmod u+rwx,g+x,o-rwx $dirs
    cd $dirs

    echo -e "Cambiando permisos ficheros .sh..."
    chmod u+x *.sh

    echo -e "Cambiando permisos ficheros .key...\n"
    chmod u+rwx,g-rwx,o-rwx *.key

    cd ..
done

cd ..

echo -e "$(getUsers)"