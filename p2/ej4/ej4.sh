#!/bin/bash
echo -e "1. Usuarios que pertenezcan a un grupo con GID igual a 46:"
echo -e "$(cat /etc/passwd | grep '\:46\:')\n"

echo -e "2) Usuarios cuyo nombre empiece y acabe con la misma letra:"
echo -e "$(cat /etc/passwd | grep -o '^[^:]*' | grep -E '^[a-z]$|^([a-z]).*\1$')\n"

echo -e "3) Usuarios cuyo nombre no contenga la letra a/A:"
echo -e "$(cat /etc/passwd | grep -v '^[^:]*[aA]')\n"

echo -e "4) Usuarios con UID de 4 digitos:"
echo -e "$(cat /etc/passwd | grep '\x\:[0-9][0-9][0-9][0-9]\:')\n"

echo -e "5) Usuarios con nombre entre 3 y 5 caracteres"

for line in $(cat /etc/passwd); do
    user=$(echo $line | grep -o '^[^:]*')
    if [ ${#user} -le 5 ] && [ ${#user} -ge 3 ]; then
        echo -e "$line"
    fi
done