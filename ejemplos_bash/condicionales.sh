echo "Nombre: "
read nombre

if [ $nombre == $USER ];
then
    echo "Bienvenido/a $nombre"

else 
    echo "ERROR"

fi