#include "brainfq.h"

int loadsourcefl(char **const read, const char *const flname)
{
    bool incomment=false;
    char cursor;
    int sourcesize=0;

    *read= NULL;

    FILE *sourcefl= fopen(flname, "r");                         //open source file in read only mode

    if(sourcefl==NULL)                                          //check for file error
    {
        printf("[@Error] Source file not found.\n");
        return 0;
    }

    while(fscanf(sourcefl, "%c", &cursor)!=EOF)                 //iterate through all characters in the file
    {
        if(cursor=='?')                                         //begin or end of a comment
        {
            incomment= !incomment;
        }

        if(cursor=='\n')                                        //end of comment at the end of a line
        {
            incomment= false;
        }

        if(!incomment)                                          //check if inside a comment
        {
            if((cursor!=' ')&&(cursor!='\n')&&(cursor!='\t'))   //add only relevant characters to the source string
            {
                if(!addtosource(read, &sourcesize, cursor))     //check for memory allocation error
                {
                    return 0;
                }
            }
        }
    }

    fclose(sourcefl);                                           //close file and return amount of read commands
    return sourcesize;
}


bool addtosource(char **read, int *const sourcesize, const char cursor)
{
    if((*sourcesize)%16==0)                                         //check if the end of another 16byte block is reached
    {
        *read= realloc(*read, ((*sourcesize)+16) * sizeof(char));   //allocate another 16 bytes and check for memory allocation error
        if(*read==NULL)
        {
            printf("[@Error] Memory allocation error, for new cmd string element.\n");
            return false;
        }
    }

    (*read)[*sourcesize]= cursor;                                   //set new byte

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

    FILE *sourcefl= fopen(flname, "rb");                                    //open brainfq file in binary read only mode

    if(sourcefl==NULL)                                                      //check for file error
    {
        printf("[@Error] Brainfq file not found.\n");
        return 0;
    }

    while(fscanf(sourcefl, "%c", &cursor)==1)                               //iterate through all bytes in the file
    {
        if(jmp>=0)                                                          //only interpret commands
        {
            if(cursor==9)                                                   //check for function indicator
            {
                infunction= !infunction;

                if(infunction)                                              //if new function is reached
                {
                    (*funamount)++;

                    *code= realloc(*code, (*funamount) * sizeof(uint8_t*)); //allocate new function array

                    if(*code!=NULL)                                         //check for memory allocation error
                    {
                        (*code)[(*funamount)-1]= NULL;
                    }
                    else
                    {
                        printf("[@Error] Memory allocation error, for new byte code function amount.\n");
                        return 0;
                    }
                }

                if(!addtosource(code[(*funamount)-1], &sourcesize, cursor)) //add function indicator
                {
                    return 0;
                }

                if(!infunction)                                             //add end of string symbol at end of function array
                {
                    if(!addtosource(code[(*funamount)-1], &sourcesize, '\0'))
                    {
                        return 0;
                    }
                }
            }
            else
            {


                if(infunction)                                              //only interpret commands inside a function; may be used to save meta info inside the byte code file
                {
                    if((cursor==5)||(cursor==6))                            //if the command expects another data 4 bytes (integer)
                    {
                        jmp=-5;                                             //set the amount of bytes to not interpret, since they are data bytes
                    }
                    else if((cursor>=1)&&(cursor<=4))                       //if command expects another data byte
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
            if(!addtosource(code[(*funamount)-1], &sourcesize, cursor))     //add data bytes to function array
            {
                return 0;
            }
        }

        jmp++;
    }

    if(jmp<0)                                                               //check for missing data bytes
    {
        printf("[@Error] Corrupted bytecode file.\n");
        printf("[@Error] Expected at least another '%d' bytes of code.\n", jmp * (-1) );
    }

    fclose(sourcefl);                                                       //close file
    return sourcesize;
}








