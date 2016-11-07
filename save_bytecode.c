#include "brainfq.h"

int save_bytecode(const char *const flname, const uint8_t *const *const code, const int funamount)
{
    int pos,jmp,bytes=0;

    FILE *binfile= fopen(flname, "wb");

    if(binfile==NULL)
    {
        printf("[@Error] File error for new byte code file.\n");
        return false;
    }

    for(int curfunction=0; curfunction<funamount; curfunction++)
    {
        pos=0;
        jmp=0;

        do
        {
            fprintf(binfile, "%c", code[curfunction][pos]);
            if(jmp>=0)
            {
                if((code[curfunction][pos]==5)||(code[curfunction][pos]==6))
                {
                    jmp=-5;
                }
                if((code[curfunction][pos]>=1)&&(code[curfunction][pos]<=4))
                {
                    jmp=-2;
                }
            }

            pos++;
            jmp++;
        }
        while(!((code[curfunction][pos]==9)&&(jmp>=0)));

        fprintf(binfile, "%c", code[curfunction][pos]);
        bytes=pos+1;
    }

    fclose(binfile);
    return bytes;
}
