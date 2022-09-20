#!/bin/bash

cp ../asm .
for file in ../resources/champs/*
do
    echo "$file"
    [ -f "$file" ] || continue
    ./asm "$file" > /dev/null
done
rm -f asm

