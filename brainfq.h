

 /* Name:             brainfq.h                                                                             */
 /* Author:           Matthias Preymann, HTBL-Hollabrunn                                                    */
 /* Date:             7.11.2016                                                                             */
 /* Description:      A hobbyist implementation of a brainfuck compiler and interpreter based on bytecode   */
 /*                   there is no real purpose of existence                                                 */

 /* Version:          1.2                                                                                   */
 /* Additional files: main.c, load.c, memory.c, parse.c, parsing_functions.c, run.c, save_bytecode.c,       */
 /*                   sprint_bytecode.c                                                                     */

 /* Disclaimer:       "This software is provided as it is and the author does not take any responsibility   */
 /*                   for any kind of damage caused by the usage of this code. Copying, sharing and the     */
 /*                   usage in any commercial or none commercial way is explicitly allowed."                */

 /* Usage:            The program expects at least one start argument containing the path of the source     */
 /*                   file to compile / run. If there is a second start argument 'debug' or 'debug!' the    */
 /*                   debug mode is enabled and a ton of additional information about compiling and during  */
 /*                   run time is spammed into the console.                                                 */
 /*                   If the file type of the source file is not '.bfq' the compiler expects a basic or     */
 /*                   advanced brainfuck source file, which is compiled to bytecode, saved and run.         */
 /*                   Bfq-files are just opened and run.                                                    */
 /*                   Except commenting the compiler is fully capable of the basic brainfuck standard. The  */
 /*                   difference in commenting results, since the compiler interprets everything including  */
 /*                   characters and numbers. These are part of advanced brainfq. A normal comment is       */
 /*                   by a '?' infront. This declared everything until the next '?' or '\n' to be a comment.*/
 /*                   For further information how to use advanced brainfq feel free to check my GitHub page */
 /*                   out.                                                                                  */

#ifndef BRAINFQ_H_INCLUDED
#define BRAINFQ_H_INCLUDED

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern const char cmd_array[];         //all available commands


int loadsourcefl(char **const read, const char *const flname);                          //loads a source file
int loadbrainfqfl(char ***const code, const char *const flname, int *const funamount);  //loads a bytecode file
bool addtosource(char **read, int *const sourcesize, const char cursor);                //adds characters in 16 byte steps to a source file

int parse(uint8_t ***const code, const char *const source, const int sourcesize);                                               //compiles a source file to bytecode
int save_bytecode(const char *const flname, const uint8_t *const *const code, const int funamount);                             //writes bytecode to file
void sprint_bytecode(const uint8_t *const *const code, const int funamount);                                                    //prints bytecode to console
int run(const uint8_t *const *const code, int *const pointerpos, const int curfunction, const int funamount, const bool debug); //runs the brainfuck bytecode

int *getmemcell(const int position);        //get the value of a memory cell or generate one if it does not exist yet
unsigned int getmemsize();                  //get current amount of allocated memory cells

uint8_t repaeting(const char *const code, int *const pos, const int codesize, const char op);   //counts the amount of repeating commands in a source file
bool newbyte(uint8_t **const memory, int *const cmdsize);                                       //generates a new byte in a string
bool newquadbyte(uint8_t **const memory, int *const cmdsize);                                   //generates four new bytes in a string
int getquadbyte(const uint8_t *const code, int *const pos);                                     //retrieves four bytes from a string and merges them into an integer
int retrieve_constant(const char *const code, int *const pos);                               //retrieves a constant integer value from a string in the source file

#endif // BRAINFQ_H_INCLUDED


/*
    //standard brainfuck commands//

    .   7       print                                                       //*
    ,   8       get                                                         //*
    [   5   +I  loop begin if current value is not 0                        //*
    ]   6   +I  loop end -> go back to begin if current value is not 0      //*
    <   2   +B  decrement pointer                                           //*
    >   1   +B  increment pointer                                           //*
    -   4   +B  increment current value                                     //*
    +   3   +B  decrement current value                                     //*

    //additional brainfuck commands//
    $   12      get current value                                           //*
    ;   13      get current pointer position                                //*
    :   9       new function                                                //*
    #   20  +B  call function                                               //*
    ?           comment                                                     //*

    =   10  +B  set current value                                           //*
    %   11  +B  set pointer                                                 //*
    &   14      and                                                         //*
    |   15      or                                                          //*
    !   16      not                                                         //*
    ~   17      move                                                        //*
    _   18      ('+' & shift) add current value and next value              //*
    *   19      ('-' & shift) subtract next value from current value        //*

    //value types//
    0   Integer constant
    1   current value
    2   current pointer position

*/
