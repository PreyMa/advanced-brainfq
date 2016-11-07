#include "brainfq.h"

void sprint_bytecode(const uint8_t *const *const code, const int funamount)
{
    int pos, temp, curfunction;

    for(curfunction=0; curfunction<funamount; curfunction++)            //iterate through all functions
    {
        pos=1;
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

            case 10:
                pos++;
                printf("=: %d", code[curfunction][pos]);

                if(code[curfunction][pos]==0)
                {
                    pos++;
                    ((uint8_t*)&temp)[0]= code[curfunction][pos];
                    pos++;
                    ((uint8_t*)&temp)[1]= code[curfunction][pos];
                    pos++;
                    ((uint8_t*)&temp)[2]= code[curfunction][pos];
                    pos++;
                    ((uint8_t*)&temp)[3]= code[curfunction][pos];
                    printf(": %d", temp);
                }

                printf("\n");
                break;

            case 11:
                pos++;
                printf("%%: %d", code[curfunction][pos]);

                if(code[curfunction][pos]==0)
                {
                    pos++;
                    ((uint8_t*)&temp)[0]= code[curfunction][pos];
                    pos++;
                    ((uint8_t*)&temp)[1]= code[curfunction][pos];
                    pos++;
                    ((uint8_t*)&temp)[2]= code[curfunction][pos];
                    pos++;
                    ((uint8_t*)&temp)[3]= code[curfunction][pos];
                    printf(": %d", temp);
                }

                printf("\n");
                break;

            case 12:
                printf("$\n");
                break;

            case 13:
                printf(";\n");
                break;

            case 14:
                printf("&\n");
                break;

            case 15:
                printf("|\n");
                break;

            case 16:
                printf("!\n");
                break;

            case 17:
                printf("~\n");
                break;

            case 18:
                printf("_\n");
                break;

            case 19:
                printf("*\n");
                break;

            default:
                printf("\n");
                break;
            }

            pos++;
        }
    }
}

