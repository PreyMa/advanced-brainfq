#include "brainfq.h"

uint8_t repaeting(const char *const code, int *const pos, const int codesize, const char op)
{
    uint8_t amount=0;

    while((*pos<codesize)&&(amount<256)&&(code[*pos]==op))      //count amount of the same character until max value of one byte
    {
        amount ++;
        (*pos)++;
    }
    return amount;                                              //return amount
}

bool newbyte(uint8_t **const memory, int *const cmdsize)
{
    (*cmdsize)++;

    *memory= realloc(*memory, (*cmdsize) * sizeof(uint8_t));    //allocate new byte and check for allocation error
    if(*memory==NULL)
    {
        printf("[@Error] Memory allocation error, for new byte code element.\n");
        printf("[@Error] Occured after element '%d'.\n", (*cmdsize)-1);
        return false;
    }

    (*memory)[(*cmdsize)-1]=0;                                  //set new byte to 0

    return true;
}

bool newquadbyte(uint8_t **const memory, int *const cmdsize)
{
    int runto= (*cmdsize)+4;

    while((*cmdsize)<runto)                                     //allocate four new bytes
    {
        (*cmdsize)++;

        *memory= realloc(*memory, (*cmdsize) * sizeof(uint8_t));
        if(*memory==NULL)                                       //check for allocation error
        {
            printf("[@Error] Memory allocation error, for new byte code element.\n");
            return false;
        }

        (*memory)[(*cmdsize)-1]=0;                              //set every new byte to 0
    }

    return true;
}

int getquadbyte(const uint8_t *const code, int *const pos)
{
    int value;

    memcpy(&value, code + *pos+ 1 , 4);         //merge four bytes into one integer

    (*pos)= (*pos)+ 4;

    return value;
}



