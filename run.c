#include "brainfq.h"

int run(const uint8_t *const *const code, int *const pointerpos, const int curfunction, const int funamount, const bool debug)
{
    int pos=1, temp, last_cmd;

    if(curfunction>=funamount)
    {
        printf("[@Error] Calling unknown function '%d'.\n", curfunction);
        return 0;
    }

    while(code[curfunction][pos]!=9)                                    //run until the end of the current function is reached
    {
        last_cmd= code[curfunction][pos];

        switch(code[curfunction][pos])                                  //enter state machine and execute current command
        {
        case 1:
            pos++;

            (*pointerpos)= (*pointerpos)+ (int) code[curfunction][pos];
            if(getmemcell(*pointerpos)==NULL)
            {
                return 0;
            }
            break;

        case 2:
            pos++;

            (*pointerpos)= (*pointerpos)- (int) code[curfunction][pos];
            if(getmemcell(*pointerpos)==NULL)
            {
                return 0;
            }
            break;

        case 3:
            pos++;

            if(getmemcell(*pointerpos)==NULL)
            {
                return 0;
            }
            (*getmemcell(*pointerpos))= (*getmemcell(*pointerpos))+ (int) code[curfunction][pos];
            break;

        case 4:
            pos++;

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
            break;

        case 7:
            if(getmemcell(*pointerpos)==NULL)
            {
                return 0;
            }
            printf("%c", *getmemcell(*pointerpos));
            break;

        case 8:
            scanf("%c", (char*) getmemcell(*pointerpos));
            break;

        case 10:
            pos++;                                                          //check value type
            if(code[curfunction][pos]==0)
            {
                (*getmemcell(*pointerpos))= getquadbyte(code[curfunction], &pos);
            }
            else if(code[curfunction][pos]==1)
            {
                //*getmemcell(*pointerpos)= *getmemcell(*pointerpos);           //useless and not used due to performance
            }
            else if(code[curfunction][pos]==2)
            {
                (*getmemcell(*pointerpos))= *pointerpos;
            }
            else
            {
                printf("[@Error] Corrupted value type identifier.\n");
                return 0;
            }
            break;

        case 11:
            pos++;                                                              //check value type
            if(code[curfunction][pos]==0)
            {
                (*pointerpos)= getquadbyte(code[curfunction], &pos);
            }
            else if(code[curfunction][pos]==1)
            {
                (*pointerpos)= *getmemcell(*pointerpos);
            }
            else if(code[curfunction][pos]==2)
            {
                // (*pointerpos)= *pointerpos;                                  //useless and not used due to performance
            }
            else
            {
                printf("[@Error] Corrupted value type identifier.\n");
                return 0;
            }
            break;

        case 12:
        case 13:
            printf("[@Error] Value identifier out of context.\n");
            break;

        case 14:
            (*getmemcell(*pointerpos))= (*getmemcell(*pointerpos)) && (*getmemcell((*pointerpos)+1));
            break;

        case 15:
            (*getmemcell(*pointerpos))= (*getmemcell(*pointerpos)) || (*getmemcell((*pointerpos)+1));
            break;

        case 16:
            (*getmemcell(*pointerpos))= !(*getmemcell(*pointerpos));
            break;

        case 17:
            (*getmemcell(*getmemcell((*pointerpos)+1)))= (*getmemcell(*pointerpos));
            break;

        case 18:
            (*getmemcell(*pointerpos))= (*getmemcell(*pointerpos)) + (*getmemcell((*pointerpos)+1));
            break;

        case 19:
            (*getmemcell(*pointerpos))= (*getmemcell(*pointerpos)) - (*getmemcell((*pointerpos)+1));
            break;

        case 20:
            pos++;                                                              //check value type
            if(code[curfunction][pos]==0)
            {
                if(!run(code, pointerpos, getquadbyte(code[curfunction], &pos), funamount, debug))
                {
                    return 0;
                }
            }
            else if(code[curfunction][pos]==1)
            {
                if(!run(code, pointerpos, *getmemcell(*pointerpos), funamount, debug))
                {
                    return 0;
                }
            }
            else if(code[curfunction][pos]==2)
            {
                if(!run(code, pointerpos, *pointerpos, funamount, debug))
                {
                    return 0;
                }
            }
            else
            {
                printf("[@Error] Corrupted value type identifier.\n");
                return 0;
            }
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

    return true;
}

