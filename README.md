# corewar
a mini-assembler and a VM that executes bytecode generated by that assembler

# about
Assembler made by [Durinder](https://github.com/Durinder)

VM made by [rikikoo](https://github.com/rikikoo)


In this "final" 42 school's group project the goal is to replicate perfectly the behaivor of the executables `asm` and `corewar`.
Apparently the `corewar` binary is based on an 80s "programming game" [Core War](https://en.wikipedia.org/wiki/Core_War).
Just like in the original game, the VM places player-written programs in its memory and lets them try to fill the memory and "stay alive", until certain conditions have been met.


Usually the _subject_ of a project, a.k.a. the project description provided to the students by the school, have clearly defined requirements what needs to be accomplished.
This time though, the school intentionally has made the subject nearly incomprehensible.
There are clues and some useful info which help, but most of the work in the completion of this project is getting your head around the inner workings of the two provided binaries, through reverse engineering. 


The students are provided with the executables (`resources/asm` and `resources/corewar`), a header file (`resources/op.h`) and a source file (`resources/op.c`).

# asm
`asm` is an assembler. It takes a single `.s` file as an argument and produces a `.cor` file to the same directory the `.s` file was in.
An `.s` file is a source code file that has Assembly-like syntax. `asm` parses the `.s` file contents and if the syntax is valid, a byte code file `.cor` is written out.
This byte code has a specific structure, which the VM `corewar` parses and executes. More on this structure later.

# corewar
`corewar` is a "virtual machine". It takes 1 to 4 `.cor` files as arguments. One `.cor` file represents a _champion_.
It places the champions inside its virtual memory (often referred to as the _arena_) and starts executing the byte code in the reverse order that the `.cor` files were given to the program (unless the "player number" flag `-n` was used) and in the order that the _statements_/_instructions_ were written in each champion's corresponding `.s` file.


During execution, after a certain amount of _cycles_, it is checked that each **Program Counter** or **PC** (which point to a memory address in the virtual memory, i.e. the current instruction) has executed at least one `live` instruction. If no `live` instructions were executed by a PC, that PC "dies". If a PC executes a `live` instruction and its argument value corresponds to a champion/player number, that player is marked as the last one to be alive.

The amount of cycles when this kind of check is done is reduced depending on various conditions (explained later). Once this `CYCLE_TO_DIE` goes to zero or below, checks for alive PCs are carried out every cycle. The game ends after all PCs have died. The last player that was reported to be alive wins.
