#include "brainfq.h"

int parse(uint8_t ***const code, const char *const source, const int sourcesize)
{
    int funamount=0, cmdamount=0, *loop_stack=NULL, loop_depth=0;
    bool infunction=false;

    *code= NULL;

    for(int i=0; i<sourcesize; i++)
    {
        if(source[i]==':')
        {
            infunction=!infunction;

            if(infunction)
            {
                funamount++;

                *code= realloc(*code, funamount * sizeof(uint8_t*));

                if(*code!=NULL)
                {
                    (*code)[funamount-1]= NULL;
                }
                else
                {
                    printf("[@Error] Memory allocation error, for new byte code function amount.\n");
                    return 0;
                }
            }

            if(!newbyte(&((*code)[funamount-1]), &cmdamount))
            {
                return 0;
            }
            (*code)[funamount-1][cmdamount-1]= 9;

            if(!infunction)
            {
                if(!newbyte(&((*code)[funamount-1]), &cmdamount))
                {
                    return 0;
                }
                (*code)[funamount-1][cmdamount-1]= '\0';
            }
        }
        else
        {
            if(infunction)
            {
                switch(source[i])
                {

                case '>':
                    //if(!newbyte(&((*code)[funamount-1]), &cmdamount))
                    if(!newbyte(code[funamount-1], &cmdamount))
                    {
                        return 0;
                    }
                    (*code)[funamount-1][cmdamount-1]= 1;
                    if(!newbyte(&((*code)[funamount-1]), &cmdamount))
                    {
                        return 0;
                    }
                    (*code)[funamount-1][cmdamount-1]= repaeting(source, &i, sourcesize, '>');
                    i--;
                    break;

                case '<':
                    if(!newbyte(&((*code)[funamount-1]), &cmdamount))
                    {
                        return 0;
                    }
                    (*code)[funamount-1][cmdamount-1]= 2;
                    if(!newbyte(&((*code)[funamount-1]), &cmdamount))
                    {
                        return 0;
                    }
                    (*code)[funamount-1][cmdamount-1]= repaeting(source, &i, sourcesize, '<');
                    i--;
                    break;

                case '+':
                    if(!newbyte(&((*code)[funamount-1]), &cmdamount))
                    {
                        return 0;
                    }
                    (*code)[funamount-1][cmdamount-1]= 3;
                    if(!newbyte(&((*code)[funamount-1]), &cmdamount))
                    {
                        return 0;
                    }
                    (*code)[funamount-1][cmdamount-1]= repaeting(source, &i, sourcesize, '+');
                    i--;
                    break;

                case '-':
                    if(!newbyte(&((*code)[funamount-1]), &cmdamount))
                    {
                        return 0;
                    }
                    (*code)[funamount-1][cmdamount-1]= 4;
                    if(!newbyte(&((*code)[funamount-1]), &cmdamount))
                    {
                        return 0;
                    }
                    (*code)[funamount-1][cmdamount-1]= repaeting(source, &i, sourcesize, '-');
                    i--;
                    break;

                case '[':
                    if(!newbyte(&((*code)[funamount-1]), &cmdamount))
                    {
                        return 0;
                    }
                    (*code)[funamount-1][cmdamount-1]= 5;

                    loop_depth++;
                    loop_stack= (int*) realloc(loop_stack, loop_depth * sizeof(int));
                    if(loop_stack==NULL)
                    {
                        printf("[@Error] Memory allocation error, for new loop stack element during parsing.\n");
                        return 0;
                    }

                    //printf("In stack [: %d\n", cmdamount-1);
                    loop_stack[loop_depth-1]= cmdamount-1;

                    if(!newquadbyte(&((*code)[funamount-1]), &cmdamount))
                    {
                        return 0;
                    }
                    break;

                case ']':
                    //printf("Hinter [: %d\n", cmdamount);
                    (*code)[funamount-1][loop_stack[loop_depth-1]+1]= ((uint8_t*)&cmdamount)[0];
                    (*code)[funamount-1][loop_stack[loop_depth-1]+2]= ((uint8_t*)&cmdamount)[1];
                    (*code)[funamount-1][loop_stack[loop_depth-1]+3]= ((uint8_t*)&cmdamount)[2];
                    (*code)[funamount-1][loop_stack[loop_depth-1]+4]= ((uint8_t*)&cmdamount)[3];


                    /*int test=0;

                    ((uint8_t*)&test)[0]= (*code)[funamount-1][4];
                    ((uint8_t*)&test)[1]= (*code)[funamount-1][5];
                    ((uint8_t*)&test)[2]= (*code)[funamount-1][6];
                    ((uint8_t*)&test)[3]= (*code)[funamount-1][7];

                    printf("Hinter [: %d\n", test);*/

                    if(!newbyte(&((*code)[funamount-1]), &cmdamount))
                    {
                        return 0;
                    }
                    (*code)[funamount-1][cmdamount-1]= 6;

                    //printf("Nr: %d\n", cmdamount);

                    if(!newquadbyte(&((*code)[funamount-1]), &cmdamount))
                    {
                        return 0;
                    }

                    //printf("zeigt zu: %d\n", (*code)[funamount-1][test]);

                    (*code)[funamount-1][cmdamount-4]= ((uint8_t*)(loop_stack+loop_depth-1))[0];
                    (*code)[funamount-1][cmdamount-3]= ((uint8_t*)(loop_stack+loop_depth-1))[1];
                    (*code)[funamount-1][cmdamount-2]= ((uint8_t*)(loop_stack+loop_depth-1))[2];
                    (*code)[funamount-1][cmdamount-1]= ((uint8_t*)(loop_stack+loop_depth-1))[3];

                    /*
                    printf("Nr: %d : %d\n", cmdamount, i);


                    ((uint8_t*)&test)[0]= (*code)[funamount-1][29];
                    ((uint8_t*)&test)[1]= (*code)[funamount-1][30];
                    ((uint8_t*)&test)[2]= (*code)[funamount-1][31];
                    ((uint8_t*)&test)[3]= (*code)[funamount-1][32];

                    printf("Hinter ]: %d\n", test);*/

                    loop_depth--;
                    loop_stack= (int*) realloc(loop_stack, loop_depth * sizeof(int));
                    break;

                case '.':
                    if(!newbyte(&((*code)[funamount-1]), &cmdamount))
                    {
                        return 0;
                    }
                    (*code)[funamount-1][cmdamount-1]= 7;
                    break;

                case ',':
                    if(!newbyte(&((*code)[funamount-1]), &cmdamount))
                    {
                        return 0;
                    }
                    (*code)[funamount-1][cmdamount-1]= 8;
                    break;

                default:
                    printf("[@Error] Character out of context: '%c'.\n", source[i]);
                    break;
                }
            }
        }

    }

    return funamount;
}


