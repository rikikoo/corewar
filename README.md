# corewar
a mini-assembler and a VM that executes bytecode generated by that assembler

## about
Assembler made by [Durinder](https://github.com/Durinder)

VM made by [rikikoo](https://github.com/rikikoo)


In this "final" 42 school's group project the goal is to replicate perfectly the behaivor of the executables `asm` and `corewar`.
Apparently the `corewar` binary is based on an 80s "programming game" [Core War](https://en.wikipedia.org/wiki/Core_War).
Just like in the original game, the VM places player-written programs in its memory and lets them try to fill the memory and "stay alive", until certain conditions have been met.


Usually the _subject_ of a project, a.k.a. the project description provided to the students by the school, have clearly defined requirements what needs to be accomplished.
This time though, the school intentionally has made the subject nearly incomprehensible.
There are clues and some useful info which help, but most of the work in the completion of this project is getting your head around the inner workings of the two provided binaries, through reverse engineering. 


The students build the project based on the provided executables (`resources/asm` and `resources/corewar`), header file (`resources/op.h`), source file (`resources/op.c`) and the aforementioned subject(s) (`resources/corewar.en.pdf` and `resources/resources_corewar.en.pdf`).

## asm
`asm` is an assembler. It takes a single `.s` file as an argument and produces a `.cor` file to the same directory the `.s` file was in.
An `.s` file is a source code file that has Assembly-like syntax. `asm` parses the `.s` file contents and if the syntax is valid, a byte code file `.cor` is written out.
This byte code has a specific structure, which the VM `corewar` parses and executes. More on this structure later.

## corewar
`corewar` is a "virtual machine". It takes 1 to 4 `.cor` files as arguments. One `.cor` file represents a _champion_.
It places the champions inside its virtual memory (often referred to as the _arena_) and starts executing the byte code in the reverse order that the `.cor` files were given to the program (unless the "player number" flag `-n` was used) and in the order that the _statements_/_instructions_ were written in each champion's corresponding `.s` file.


During execution, after a certain amount of _cycles_, it is checked that each **Program Counter** or **PC** (which point to a memory address in the virtual memory, i.e. the current instruction) has executed at least one `live` instruction. If no `live` instructions were executed by a PC, that PC "dies". If a PC executes a `live` instruction and its argument value corresponds to a champion/player number, that player is marked as the last one to be alive.


The amount of cycles when this kind of check is done is reduced depending on various conditions (explained later). Once this `CYCLE_TO_DIE` goes to zero or below, checks for alive PCs are carried out every cycle. The game ends after all PCs have died. The last player that was reported to be alive wins.

## byte code structure
A champion `.cor` file has the following bytes, in order, which are all defined in `op.h`:
1. `0x00ea83f3`, a magic header, as defined by `COREWAR_EXEC_MAGIC`. Occupies the first 4 bytes.
2. The next `PROG_NAME_LENGTH` bytes are reserved for the champion name. The remaining bytes after the name in these 128 B are padded with zeros.
3. Four zero-bytes as a separator.
4. Size of the actual champion code, which can't exceed `CHAMP_MAX_SIZE` (682 B). The size info is recorded on 4 B.
5. The next `COMMENT_LENGTH` bytes are the "comment" of the champion. Again, bytes in these 2048 B after the comment text are zero-bytes.
6. Four zero-bytes as a separator.
7. The code of the champion, i.e. the statements, their _argument coding bytes_ and arguments, in the order that they were written in the corresponding `.s` file, encoded as described in the following section.

## statements
The below table is a summary. It does not contain all the information that is related to each statement and the procedures going on in the VM.

| name | encoding byte (hex) | no. of arguments | description |
| ---- | ------------- | ---------------- | ----------- |
| `live` | `01` | 1 | keeps a process alive and marks the player whose number is in the 1st agrument (as a negative value) as being alive |
| `ld` | `02` | 2 | **load**: writes the 1st arg's value into the register given in the 2nd arg |
| `st` | `03` | 2 | **store**: writes the value inside the register given in the 1st arg into the address given in the 2nd arg |
| `add` | `04` | 3 | **add**: performs addition to the 1st and 2nd arg values and writes the result into the register given as the 3rd arg |
| `sub` | `05` | 3 | **subtract**: exactly the same as `add`, but performs subtraction |
| `and` | `06` | 3 | **logical AND**: same as above, but performs AND operation |
| `or` | `07` | 3 | **logical OR**: same as above, but performs OR operation |
| `xor` | `08` | 3 | **logical XOR**: same as above, but performs XOR operation |
| `zjmp` | `09` | 1 | **zero jump**: updates address/position of a PC to current address + 1st arg value, if `carry == 0` |
| `ldi` | `0a` | 3 | **load from index**: defines address where to read value from by adding the first two args together and writing the value read at that address into the register given as 3rd arg |
| `sti` | `0b` | 3 | **store to index**: 1st arg is the register we get the value from and 2nd and 3rd args form the address we will write the value to |
| `fork` | `0c` | 1 | **fork**: clones the PC into the address given as the 1st arg |
| `lld` | `0d` | 2 | **long load**: same as `ld`, except if the _argument type_ is of type **indirect** (`T_IND`), the address we read the value from can be read from a farther address than what `ld` allows |
| `lldi` | `0e` | 3 | **long load from index**: same as `ldi`, but with the logic described above, in `lld`'s description |
| `lfork` | `0f` | 1 | **long fork**: same as `fork` but can clone the PC farther away than `fork` |
| `aff` | `10` | 1 | attempts to convert the value inside the register given as the 1 st argument to `char` and print it during execution |


The statements have different kinds of attributes associated with them. The `op.c` has these attributes listed per statement. Only thing is, there's no mention in the file that would explain which value corresponds to which attribute. After figuring it out, these turn out to be their meaning:
```
{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0}
   |     |     |     |   |     |     |  |
   |     |     |     |   |     |     |  └ has reduced T_DIR size (4B --> 2B)?
   |     |     |     |   |     |     └ has ACB (argument coding byte)?
   |     |     |     |   |     └ description
   |     |     |     |   └ wait cycles
   |     |     |     └ statement code
   |     |     └ argument types (separated by |)
   |     └ number of arguments
   └ statement name
```

## virtual machine
The VM has "internal" memory of `MEM_SIZE` bytes (4096), which represents the "arena" where all the champions' code is placed in.

The champions are placed evenly on the arena and one PC is placed on the first byte of each champ's code. The PCs, one at a time, start reading the bytes they are on and executing them if they're valid. Once every PC has tried to execute or indeed executed the instruction they are currently on, a cycle ends and the next one begins.

Each statement/instruction has a different waiting time associated with them. A PC doesn't execute the instruction until the wait time has ended.

If the instruction a PC is on is valid and the wait time has ended, the instruction is executed, no matter which champion's code it is. After performing the statement, the PC jumps to the next statement.
If the instruction is invalid, the statement is skipped completely.

There is a so-called "cycle to die" check performed periodically. The check interval is initially `CYCLE_TO_DIE` cycles (1536). During this check, all PCs that haven't performed a `live` statement are removed from the game.
In order for the game to end at some point, there are built-in conditions when the `CYCLE_TO_DIE` is reduced. This reduction happens during a check if...
- the number of `live` statements is equal to or greater than `NBR_LIVE` (21) or
- no reduction has been done in the last `MAX_CHECKS` (10) checks.

The amount that is subtracted from `CYCLE_TO_DIE` is defined to be `CYCLE_DELTA` (50). Once `CYCLE_TO_DIE` <= 0, a check is performed on every cycle. The game ends after all PCs are dead.



## usage
Installation:
```
git clone https://github.com/rikikoo/corewar.git
cd corewar
git submodule init libft
git submodule update
make all
```

Create a `.cor` from an `.s` file:
`asm resources/champs/<name_of_champion>.s`


Run corewar:
```
./corewar [-dump N] [-s N] [-l] [-v N] [-n N] <champion1.cor> <...>	

************************************************************	

dump: executes up to N cycles after which memory is dumped to STDOUT
   s: dumps memory after every N cycles and continues exeution	
   l: changes row length of -dump and -s from 32 to 64 bytes per row	
   v: verbose level, add together Ns below for combined verbosity
    1: print cycles and CYCLE_TO_DIE reductions	
    2: print valid executed instructions	
    4: print invalid instruction execution attempts	
    8: print lives and deaths of processes	
    16: dump memory after the game has ended successfully	
    31: full verbosity	
   n: N [1...4] assigns the following champion's player number
```

Example:
`corewar -v 15 resources/champs/toto.cor -n 1 resources/champs/jumper.cor resources/champs/Gagnant.cor`


