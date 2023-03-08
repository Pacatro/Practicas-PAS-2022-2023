#!/bin/bash
mover_archivos(){
    cd ../skel
    for file in $(ls); do
        cp $file ../homes/$user
    done
    cd ..
}

crear_usuario(){
    cd homes/
    
    if [ -d $user ]; then
        echo -e "El usuario $user ya existe\nSaliendo..."
        exit
    fi

    mkdir $user
    mover_archivos $user

    echo $user >> users.txt
    echo -e "Se ha creado el usuario $user."
}

if [ $# != 1 ]; then
    echo -e "Argumentos incorrectos.\nUso: ./ejercicio6.sh <usuario>"
    exit
fi

user=$1

if !([ -f users.txt ]); then 
    touch users.txt
fi

if !([ -d homes ]); then
    mkdir homes
fi

crear_usuario $user
