#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "proc.h"

//#define STACK_POP_(val_) if ()          // ???

int main(void)
{
    FILE* program_file = fopen("program.txt", "r");
    if (program_file == NULL)
    {
        fprintf(stdout, "An error occured while opening program file\n");
        fprintf(stdout, "We must stop the program\n");
        return 1;
    }

    FILE* err_file = freopen("errors.txt", "w", stderr);
    if (err_file == NULL)
    {
        fprintf(stdout, "An error occured while opening error file\n");
        fprintf(stdout, "We must stop the program\n");
        fclose(program_file);
        return 1;
    }

    Stack_t stk = {};
    StackSize_t capacity = 5;

    if (StackConstructor(&stk, capacity) != STACK_CTOR_SUCCESS)
    {
        StackStop(&stk, err_file);
        StackDestructor(&stk);
        fclose(err_file);
        fclose(program_file);
        return 1;
    }

    if (AssembleProgram(program_file))
    {
        fprintf(stderr, "failed to assemble program\n\n");
    }

    FILE* commands_file = fopen("commands.txt", "r");
    if (commands_file == NULL)
    {
        fprintf(stdout, "An error occured while opening commands file\n");
        fprintf(stdout, "We must stop the program\n");
        fprintf(stderr, "failed to open commands file\n\n");
        fclose(program_file);
        fclose(err_file);
        return 1;
    }

    RunProgram(commands_file, &stk);

    StackDestructor(&stk);
    fclose(program_file);
    fclose(commands_file);
    fclose(err_file);

    return 0;
}

//#undef STACK_POP_
