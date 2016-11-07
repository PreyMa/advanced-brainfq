#include "brainfq.h"

int run(const uint8_t *const *const code, int *const pointerpos, const int curfunction, const int funamount, const bool debug)
{
    int pos=1, temp, last_cmd;

    while(code[curfunction][pos]!=9)
    {
        //printf("%d: %d: ", pos, code[curfunction][pos]);
        last_cmd= code[curfunction][pos];

        switch(code[curfunction][pos])
        {
        case 1:
            //printf(">: ");
            pos++;
            //printf("%d\n", code[curfunction][pos]);

            (*pointerpos)= (*pointerpos)+ (int) code[curfunction][pos];
            if(getelement(*pointerpos)==NULL)
            {
                return 0;
            }
            break;

        case 2:
            //printf("<: ");
            pos++;
            //printf("%d\n", code[curfunction][pos]);

            (*pointerpos)= (*pointerpos)- (int) code[curfunction][pos];
            if(getelement(*pointerpos)==NULL)
            {
                return 0;
            }
            break;

        case 3:
            //printf("+: ");
            pos++;
            //printf("%d\n", code[curfunction][pos]);

            if(getelement(*pointerpos)==NULL)
            {
                return 0;
            }
            (*getelement(*pointerpos))= (*getelement(*pointerpos))+ (int) code[curfunction][pos];
            break;

        case 4:
            //printf("-: ");
            pos++;
            //printf("%d\n", code[curfunction][pos]);

            if(getelement(*pointerpos)==NULL)
            {
                return 0;
            }
            (*getelement(*pointerpos))= (*getelement(*pointerpos))- (int) code[curfunction][pos];
            break;

        case 5:
            temp= getquadbyte(code[curfunction], &pos);
            if(getelement(*pointerpos)==NULL)
            {
                return 0;
            }
            if(*(getelement(*pointerpos))==0)
            {
                pos= temp+4;
            }

            //printf("[: %d\n", temp);
            break;

        case 6:
            temp= getquadbyte(code[curfunction], &pos);
            if(getelement(*pointerpos)==NULL)
            {
                return 0;
            }
            if(*(getelement(*pointerpos))!=0)
            {
                pos= temp+4;
            }
            //printf("]: %d\n", temp);
            break;

        case 7:
            if(getelement(*pointerpos)==NULL)
            {
                return 0;
            }
            printf("%c", *getelement(*pointerpos));
            //printf(".\n");
            break;

        case 8:
            scanf("%c", getelement(*pointerpos));
            //printf(",\n");
            break;

        default:
            printf("[@Error] Command out of context.\n");
            //printf("\n");
            break;
        }

        if(debug)
        {
            printf("cmd: %d:%c func: %d pos: %d val: %d\n", pos, cmd_array[last_cmd-1], curfunction, *pointerpos, *getelement(*pointerpos));
        }

        pos++;
    }
}

