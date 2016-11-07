#include "brainfq.h"

int getquadbyte(const uint8_t *const code, int *const pos)
{
    int value;

    (*pos)++;
    ((uint8_t*)&value)[0]= code[*pos];
    (*pos)++;
    ((uint8_t*)&value)[1]= code[*pos];
    (*pos)++;
    ((uint8_t*)&value)[2]= code[*pos];
    (*pos)++;
    ((uint8_t*)&value)[3]= code[*pos];

    return value;
}
