#!/bin/bash

for file in vm_champs/champs/*
do
    echo "$file"
    [ -f "$file" ] || continue
    ./asm "$file" > /dev/null
done
