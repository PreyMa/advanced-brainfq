#include "brainfq.h"

int run(const uint8_t *const *const code, int *const pointerpos, const int curfunction, const int funamount, const bool debug)
{
    int pos=1, temp, last_cmd;

    while(code[curfunction][pos]!=9)                                    //run until the end of the current function is reached
    {
        //printf("%d: %d: ", pos, code[curfunction][pos]);
        last_cmd= code[curfunction][pos];

        switch(code[curfunction][pos])                                  //enter state machine and execute current command
        {
        case 1:
            //printf(">: ");
            pos++;
            //printf("%d\n", code[curfunction][pos]);

            (*pointerpos)= (*pointerpos)+ (int) code[curfunction][pos];
            if(getmemcell(*pointerpos)==NULL)
            {
                return 0;
            }
            break;

        case 2:
            //printf("<: ");
            pos++;
            //printf("%d\n", code[curfunction][pos]);

            (*pointerpos)= (*pointerpos)- (int) code[curfunction][pos];
            if(getmemcell(*pointerpos)==NULL)
            {
                return 0;
            }
            break;

        case 3:
            //printf("+: ");
            pos++;
            //printf("%d\n", code[curfunction][pos]);

            if(getmemcell(*pointerpos)==NULL)
            {
                return 0;
            }
            (*getmemcell(*pointerpos))= (*getmemcell(*pointerpos))+ (int) code[curfunction][pos];
            break;

        case 4:
            //printf("-: ");
            pos++;
            //printf("%d\n", code[curfunction][pos]);

            if(getmemcell(*pointerpos)==NULL)
            {
                return 0;
            }
            (*getmemcell(*pointerpos))= (*getmemcell(*pointerpos))- (int) code[curfunction][pos];
            break;

        case 5:
            temp= getquadbyte(code[curfunction], &pos);
            if(getmemcell(*pointerpos)==NULL)
            {
                return 0;
            }
            if(*(getmemcell(*pointerpos))==0)
            {
                pos= temp+4;
            }

            //printf("[: %d\n", temp);
            break;

        case 6:
            temp= getquadbyte(code[curfunction], &pos);
            if(getmemcell(*pointerpos)==NULL)
            {
                return 0;
            }
            if(*(getmemcell(*pointerpos))!=0)
            {
                pos= temp+4;
            }
            //printf("]: %d\n", temp);
            break;

        case 7:
            if(getmemcell(*pointerpos)==NULL)
            {
                return 0;
            }
            printf("%c", *getmemcell(*pointerpos));
            //printf(".\n");
            break;

        case 8:
            scanf("%c", getmemcell(*pointerpos));
            //printf(",\n");
            break;

        default:
            printf("[@Error] Command out of context.\n");
            //printf("\n");
            break;
        }

        if(debug)                                           //some debug information
        {
            printf("cmd: %d:%c func: %d pos: %d val: %d\n", pos, cmd_array[last_cmd-1], curfunction, *pointerpos, *getmemcell(*pointerpos));
        }

        pos++;
    }
}

