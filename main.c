#include "brainfq.h"

const char cmd_array[9]= {'>','<','+','-','[',']','.',',',':'};

int main(const int argc, const char *const *const argv)
{
    bool debug=false, edebug=false;
    char *source;
    int sourcesize, funamount, pointerpos=0, bytecode_size;
    uint8_t **bytecode;

    printf("Advanced Brainfq Compiler and Interpreter by Matthias Preymann:\n\n");

    if(argc>=2)
    {
        if(argc>=3)
        {
            if(strcmp(argv[2], "debug")==0)
            {
                debug=true;
                printf("[@Info] Enabled debug mode: Expect lots of spam in the console and a bad performance.\n");
            }
            else if(strcmp(argv[2], "debug!")==0)
            {
                debug=true;
                edebug=true;
                printf("[@Info] Enabled EXTENDET debug mode: Expect lots of spam in the console and a bad performance.\n");
                printf("[@Info] The compiled bytecode will be displayed additionally.\n");
                printf("[@Info] (This feature is rather useless.)\n");
            }
        }

        if(strcmp(argv[1]+strlen(argv[1])-4, ".bfq")==0)
        {

            printf("[@Info] Reading brainfq file: %s\n", argv[1]);
            sourcesize= loadbrainfqfl(&bytecode, argv[1], &funamount);
            if(!sourcesize)
            {
                printf("[@Error] Corrupted or empty brainfq file.\n");
                return 1;
            }

            printf("[@Info] Done. Read '%d' bytes.\n", sourcesize);
            printf("[@Info] Brainfq file contained '%d' functions.\n", funamount);
        }
        else
        {
            printf("[@Info] Reading source file: %s\n", argv[1]);
            sourcesize= loadsourcefl(&source, argv[1]);
            if(!sourcesize)
            {
                printf("[@Error] Corrupted or empty source file.\n");
                return 1;
            }

            printf("[@Info] Done. Read source file containing '%d' characters.\n", sourcesize);
            printf("[@Info] Compiling to byte code: \n");

            funamount= parse(&bytecode, source, sourcesize);
            if(!funamount)
            {
                return 1;
            }

            printf("[@Info] Done. Loaded '%d' functions: \n", funamount);
            printf("[@Info] Printing byte code output file.\n");

            strcpy(argv[1]+strlen(argv[1])-4, ".bfq");

            bytecode_size= save_bytecode(argv[1], bytecode, funamount);
            if(!bytecode_size)
            {
                return 1;
            }

            if(edebug)
            {
                sprint_bytecode(bytecode, funamount);
            }

            printf("[@Info] Done. Printed '%d' bytes to output file.\n", bytecode_size);
        }

        printf("[@Info] Running function '0':\n");

        if(!run(bytecode, &pointerpos, 0, funamount, debug))
        {
            return 1;
        }

        printf("[@Info] Done. Ended execution.\n");
        printf("[@Info] Total memory usage of %d cells (%d bytes).\n", getmemsize(), getmemsize()* sizeof(int));

    }
    else
    {
        printf("[@Error] Expected source file name as start argument.\n");
        printf("Usage: brainfq.exe [file-name.bfq] [debug]\n");
        return 1;
    }

    return 0;
}
