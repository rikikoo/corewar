#!/bin/bash

for file in tests/error_champs/*
do
    echo "$file"
    [ -f "$file" ] || continue
    ./asm "$file" > /dev/null
done
