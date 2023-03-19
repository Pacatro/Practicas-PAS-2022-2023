#!/bin/bash
echo -e "1) Grupos que contengan al menos 1 usuario ademas del usuario principal:"
echo -e "$(cat /etc/group | grep '\:[^x][[:alpha:]].*')\n"

echo -e "2) Grupos cuyo nombre empiece por u y acabe en s:"
echo -e "$(cat /etc/group | grep -e '^u.*s')\n"

echo -e "3) Grupos cuyo nombre contenga dos letras iguales seguidas:"
echo -e "$(cat /etc/group | grep -E '([[:alpha:]])\1')\n"

echo -e "4) Grupos que no contengan ningun usuario adicional:"
echo -e "$(cat /etc/group | grep -v '\:[^x][[:alpha:]].*')\n"

echo -e "5) Grupos con GID menor que 100:"

for line in $(cat /etc/group); do
    let group=$(echo $line | grep -o '[0-9]*')

    if [ $group -lt 100 ]; then
        echo $line
    fi
done