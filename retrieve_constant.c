#include "brainfq.h"

int retrieve_constant(const uint8_t *const code, int *const pos)
{
    char temp[32];
    int i=-1;
    bool run=true;

    do
    {
        i++;
        (*pos)++;
        temp[i]=code[*pos];

        if(!(((temp[i]>='0')&&(temp[i]<='9'))||((temp[i]>='a')&&(temp[i]<='z'))||((temp[i]>='A')&&(temp[i]<='Z'))))
        {
            if(temp[i]=='-')
            {
                if(i!=0)
                {
                    run= false;
                }
            }
            else
            {
                run= false;
            }
        }

    }
    while((i<32)&&run);

    (*pos)--;

    temp[i]= '\0';

    return atoi(temp);
}
