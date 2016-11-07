#include "brainfq.h"

void sprint_bytecode(const uint8_t *const *const code, const int funamount)
{
    int pos=1, temp, curfunction;

    for(curfunction=0; curfunction<funamount; curfunction++)            //iterate through all functions
    {
        printf("[@Debug] Printing function '%d':\n", curfunction);
        while(code[curfunction][pos]!=9)                                //iterate through all commands of a function
        {
            printf("[@Debug] %d: %d: ", pos, code[curfunction][pos]);

            switch(code[curfunction][pos])                              //enter state machine
            {
            case 1:
                printf(">: ");
                pos++;
                printf("%d\n", code[curfunction][pos]);
                break;

            case 2:
                printf("<: ");
                pos++;
                printf("%d\n", code[curfunction][pos]);
                break;

            case 3:
                printf("+: ");
                pos++;
                printf("%d\n", code[curfunction][pos]);
                break;

            case 4:
                printf("-: ");
                pos++;
                printf("%d\n", code[curfunction][pos]);
                break;

            case 5:
                pos++;
                ((uint8_t*)&temp)[0]= code[curfunction][pos];
                pos++;
                ((uint8_t*)&temp)[1]= code[curfunction][pos];
                pos++;
                ((uint8_t*)&temp)[2]= code[curfunction][pos];
                pos++;
                ((uint8_t*)&temp)[3]= code[curfunction][pos];
                printf("[: %d\n", temp);
                break;

            case 6:
                pos++;
                ((uint8_t*)&temp)[0]= code[curfunction][pos];
                pos++;
                ((uint8_t*)&temp)[1]= code[curfunction][pos];
                pos++;
                ((uint8_t*)&temp)[2]= code[curfunction][pos];
                pos++;
                ((uint8_t*)&temp)[3]= code[curfunction][pos];
                printf("]: %d\n", temp);
                break;

            case 7:
                printf(".\n");
                break;

            case 8:
                printf(",\n");
                break;

            default:
                printf("\n");
                break;
            }

            pos++;
        }
    }
}

