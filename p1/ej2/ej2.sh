#!/bin/bash

#Escribimos en un fichero txt los usuarios logueados sin repeticiones y los mostramos.
getUsers(){
    who > logged.txt | uniq logged.txt | who > /dev/null

    echo -e "Usuarios logueados en este momento:"
    echo $(cat logged.txt)
    rm -r logged.txt
}

shFiles(){
    for files_sh in $(find -name "*.sh"); do
        echo -e "Cambiando permisos ficheros .sh: $files_sh\n"
        chmod u+x $files_sh
    done
}

keyFiles(){
    for files_key in $(find -name "*.key"); do
        echo -e "Cambiando permisos ficheros .key: $files_key\n"
        chmod u+rwx,g-rwx,o-rwx $files_key
    done
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

    echo $(shFiles)
    echo $(keyFiles)

    cd ..
done

cd ..

echo -e "\n$(getUsers)"