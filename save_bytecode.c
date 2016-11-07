#include "brainfq.h"

int save_bytecode(const char *const flname, const uint8_t *const *const code, const int funamount)
{
    int pos,jmp,bytes=0;

    FILE *binfile= fopen(flname, "wb");                                     //open output file in binary write mode

    if(binfile==NULL)                                                       //check for file error
    {
        printf("[@Error] File error for new byte code file.\n");
        return false;
    }

    for(int curfunction=0; curfunction<funamount; curfunction++)            //iterate through all functions
    {
        pos=0;                                                              //reset variables
        jmp=0;

        do                                                                  //iterate through all commands of a function
        {
            fprintf(binfile, "%c", code[curfunction][pos]);
            if(jmp>=0)                                                      //only interpret commands
            {
                if((code[curfunction][pos]==5)||(code[curfunction][pos]==6))//print out four data bytes (integer)
                {
                    jmp=-5;
                }
                else if((code[curfunction][pos]>=1)&&(code[curfunction][pos]<=4))//print out one data byte
                {
                    jmp=-2;
                }
                else if((code[curfunction][pos]==10)||(code[curfunction][pos]==11))//print data bytes for value type
                {
                    jmp=-2;

                    if(code[curfunction][pos+1]==0)                                 //if data type is an integer constant print another 4 byte
                    {
                        jmp=-6;
                    }
                }
            }

            pos++;
            jmp++;
        }
        while(!((code[curfunction][pos]==9)&&(jmp>=0)));                    //run until function indicator is reached and it is actually a command

        fprintf(binfile, "%c", code[curfunction][pos]);
        bytes=pos+1;
    }

    fclose(binfile);                                                        //close file
    return bytes;                                                           //return amount of written bytes
}
