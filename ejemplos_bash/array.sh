#!/bin/bash

array[0]="1"
array2=(1 2 3)

echo ${array[0]}

echo ${array2[*]}

echo ${#array2[@]}