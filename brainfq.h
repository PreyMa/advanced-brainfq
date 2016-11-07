#ifndef BRAINFQ_H_INCLUDED
#define BRAINFQ_H_INCLUDED

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern const char cmd_array[9];


int loadsourcefl(char **const read, const char *const flname);
int loadbrainfqfl(char ***const code, const char *const flname, int *const funamount);
bool addtosource(char **read, int *const sourcesize, const char cursor);

int parse(uint8_t ***const code, const char *const source, const int sourcesize);
int save_bytecode(const char *const flname, const uint8_t *const *const code, const int funamount);
void sprint_bytecode(const uint8_t *const *const code, const int funamount);
int run(const uint8_t *const *const code, int *const pointerpos, const int curfunction, const int funamount, const bool debug);

int *getelement(const int position);
int getquadbyte(const uint8_t *const code, int *const pos);
unsigned int getmemsize();

uint8_t repaeting(const char *const code, int *const pos, const int codesize, const char op);
bool newbyte(uint8_t **const memory, int *const cmdsize);
bool newquadbyte(uint8_t **const memory, int *const cmdsize);

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
    $   get current value                                           //*
    ;   get current pointer position                                //*
    :   9   new function                                                //*
    #   call function                                               //*
    ?   comment                                                     //*

    =   set current value                                           //*
    %   set pointer                                                 //*
    &   and                                                         //*
    |   or                                                          //*
    !   not                                                         //*
    ~   move                                                        //*
    _   ('+' & shift) add current value and next value              //*
    *   ('-' & shift) subtract next value from current value        //*

*/
