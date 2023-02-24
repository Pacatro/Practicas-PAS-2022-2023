#!/bin/bash

hola(){
    echo "Estas en la funcion"
}

suma(){
    let suma=$a+$b
    echo $suma
}

echo "Llamando a funcion"
hola
echo "fin funcion"

let a=5
let b=5
suma $a $b