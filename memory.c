#include "brainfq.h"

static int memsize=0;                               //private value containing the current amount of memory cells

int *getmemcell(const int position)
{
    static int *memory=NULL;

    if(position<0)                                  //trying to call a negative cell pointer
    {
        printf("[@Error] Negative element pointer error.\n");
        return NULL;
    }

    if(position>memsize-1)                          //if memory cell out of the the current array is reached, new ones will be created
    {
        memory= (int*) realloc(memory, (position+1) * sizeof(int)); //generate new cells

        if(memory!=NULL)                            //check for allocation error
        {
            for(int i= memsize; i<=position; i++)   //set all new cells to 0
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
    return memory+position;                         //return pointer to the cell
}

unsigned int getmemsize()
{
    return memsize;                                 //return the current amount of memory cells
}


