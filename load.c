#include "brainfq.h"

int loadsourcefl(char **const read, const char *const flname)
{
    bool incomment=false;
    char cursor;
    int sourcesize=0;

    *read= NULL;

    FILE *sourcefl= fopen(flname, "r");

    if(sourcefl==NULL)
    {
        printf("[@Error] Source file not found.\n");
        return 0;
    }

    while(fscanf(sourcefl, "%c", &cursor)!=EOF)
    {
        if(cursor=='?')
        {
            incomment= !incomment;
        }

        if(cursor=='\n')
        {
            incomment= false;
        }

        if(!incomment)
        {
            if((cursor!=' ')&&(cursor!='\n')&&(cursor!='\t'))
            {
                if(!addtosource(read, &sourcesize, cursor))
                {
                    return 0;
                }
            }
        }
    }

    fclose(sourcefl);
    return sourcesize;
}


bool addtosource(char **read, int *const sourcesize, const char cursor)
{
    if((*sourcesize)%16==0)
    {
        *read= realloc(*read, ((*sourcesize)+16) * sizeof(char));
        if(*read==NULL)
        {
            printf("[@Error] Memory allocation error, for new cmd string element.\n");
            return false;
        }
    }

    (*read)[*sourcesize]= cursor;

    (*sourcesize)++;
    return true;
}

int loadbrainfqfl(char ***const code, const char *const flname, int *const funamount)
{
    char cursor;
    int sourcesize=0, jmp=0;
    bool infunction=false;

    *code= NULL;
    *funamount=0;

    FILE *sourcefl= fopen(flname, "rb");

    if(sourcefl==NULL)
    {
        printf("[@Error] Brainfq file not found.\n");
        return 0;
    }

    while(fscanf(sourcefl, "%c", &cursor)==1)
    {
        if(jmp>=0)
        {
            if(cursor==9)
            {
                infunction= !infunction;

                if(infunction)
                {
                    (*funamount)++;

                    *code= realloc(*code, (*funamount) * sizeof(uint8_t*));

                    if(*code!=NULL)
                    {
                        (*code)[(*funamount)-1]= NULL;
                    }
                    else
                    {
                        printf("[@Error] Memory allocation error, for new byte code function amount.\n");
                        return 0;
                    }
                }

                if(!addtosource(code[(*funamount)-1], &sourcesize, cursor))
                {
                    return 0;
                }

                if(!infunction)
                {
                    if(!addtosource(code[(*funamount)-1], &sourcesize, '\0'))
                    {
                        return 0;
                    }
                }
            }
            else
            {


                if(infunction)
                {
                    if((cursor==5)||(cursor==6))
                    {
                        jmp=-5;
                    }
                    else if((cursor>=1)&&(cursor<=4))
                    {
                        jmp=-2;
                    }

                    if(!addtosource(code[(*funamount)-1], &sourcesize, cursor))
                    {
                        return 0;
                    }
                }

            }
        }
        else
        {
            if(!addtosource(code[(*funamount)-1], &sourcesize, cursor))
            {
                return 0;
            }
        }

        jmp++;
    }

    fclose(sourcefl);
    return sourcesize;
}








