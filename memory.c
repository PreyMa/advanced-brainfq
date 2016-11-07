#include "brainfq.h"

static int memsize=0;

int *getelement(const int position)
{
    static int *memory=NULL;
    int i;

    if(position<0)
    {
        printf("[@Error] Negative element pointer error.\n");
        return NULL;
    }

    if(position>memsize-1)
    {
        memory= (int*) realloc(memory, (position+1) * sizeof(int));

        if(memory!=NULL)
        {
            for(i=memsize; i<=position; i++)
            {
                memory[i]= 0;
            }
            memsize= position+1;
        }
        else
        {
            printf("[@Error] Memory allocation error, for new memory element.\n");
            return NULL;
        }
    }
    return memory+position;
}

unsigned int getmemsize()
{
    return memsize;
}


