x="hola"

bash    #Creamos proceso hijo

echo $x

exit    #Volvemos al proceso padre

export x    #Exportamos la variable x
bash    #Volvemos a crear un proceso hijo
echo $x