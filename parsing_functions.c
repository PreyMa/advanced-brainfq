#include "brainfq.h"

uint8_t repaeting(const char *const code, int *const pos, const int codesize, const char op)
{
    uint8_t amount=0;

    while((*pos<codesize)&&(amount<256)&&(code[*pos]==op))
    {
        amount ++;
        (*pos)++;
    }
    return amount;
}

bool newbyte(uint8_t **const memory, int *const cmdsize)
{
    (*cmdsize)++;

    *memory= realloc(*memory, (*cmdsize) * sizeof(uint8_t));
    if(*memory==NULL)
    {
        printf("[@Error] Memory allocation error, for new byte code element.\n");
        printf("[@Error] Occured after element '%d'.\n", (*cmdsize)-1);
        return false;
    }

    (*memory)[(*cmdsize)-1]=0;

    return true;
}

bool newquadbyte(uint8_t **const memory, int *const cmdsize)
{
    int runto= (*cmdsize)+4;

    while((*cmdsize)<runto)
    {
        (*cmdsize)++;

        *memory= realloc(*memory, (*cmdsize) * sizeof(uint8_t));
        if(*memory==NULL)
        {
            printf("[@Error] Memory allocation error, for new byte code element.\n");
            return false;
        }

        (*memory)[(*cmdsize)-1]=0;
    }

    return true;
}



