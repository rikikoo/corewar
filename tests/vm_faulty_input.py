#! /usr/bin/env python3

import subprocess as sp
import os

tests = {
    "No arguments given": \
        ["../corewar"],
    "Invalid flag only": \
        "../corewar -r".split(),
    "Invalid flag with a valid .cor file": \
        "../corewar -r ../resources/champs/Car.cor".split(),
    "Invalid flag amidst valid flags with a valid .cor file": \
        "../corewar -v 8 -r -dump 1000 ../resources/champs/Car.cor".split(),
    "Verbose flag with invalid value (0)": \
        "../corewar -v 0 ../resources/champs/Car.cor".split(),
    "Verbose flag with invalid value (-2)": \
        "../corewar -v -2 ../resources/champs/Car.cor".split(),
    "Dump flag with invalid value (0)": \
        "../corewar -dump 0 ../resources/champs/Car.cor".split(),
    "Dump flag with invalid value (-2)": \
        "../corewar -dump -2 ../resources/champs/Car.cor".split(),
    "Too many champions": \
        "../corewar ../resources/champs/Gagnant.cor ../resources/champs/Car.cor ../resources/champs/ex.cor ../resources/champs/toto.cor ../resources/champs/jumper.cor".split(),
    "Player number flag with invalid value (0)": \
        "../corewar ../resources/champs/toto.cor -n 0 ../resources/champs/ex.cor ../resources/champs/slider2.cor".split(),
    "Player number flag with invalid value (7)": \
        "../corewar ../resources/champs/toto.cor -n 7 ../resources/champs/ex.cor ../resources/champs/slider2.cor".split(),
    "Player number flag with invalid value (-4)": \
        "../corewar ../resources/champs/toto.cor -n -4 ../resources/champs/ex.cor ../resources/champs/slider2.cor".split(),
    ".cor file with incorrect header": \
        "../corewar test_champs/noheader.cor".split(),
    "Non .cor file": \
        "../corewar ../asm".split(),
    ".core file": \
        "../corewar test_champs/ex.core".split(),
    "Champ name too long": \
        "../corewar test_champs/longname.cor".split(),
    "Champ comment too long": \
        "../corewar test_champs/longcomment.cor".split(),
    "Champ exec size too long": \
        "../corewar test_champs/oversized.cor".split(),
    "Champ reported size doesn't match actual size": \
        "../corewar test_champs/size_mismatch.cor".split()
}

ans = input("Begin a series of tests against the corewar VM (../corewar)? (y/n) ")
if ans.lower() == 'n':
    quit()
i = 1
for test_name, test_cmd in tests.items():
    print(f"\n******************** TEST {i} ********************\n")
    run = sp.run(test_cmd, stdout=True)
    print(f"\nTest was '{test_name}':\n{' '.join(test_cmd)}\n")
    ans = input("\nThere should be an error message or the program usage above. Is it so? (y/n) ")
    if ans.lower() == 'n':
        print("\nDamn... that's a fail then.")
        print(f"Test {i}: '{test_name}' failed.\n")
        ans = input("Continue? (y/n) ")
        if ans.lower() == 'n':
            quit()
    print("\n")
    i += 1

print("\nTests completed.")
