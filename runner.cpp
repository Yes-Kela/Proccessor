/* runner */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "runner.h"

void RunProgram(FILE* commands_file, Stack_t* stk)
{
    Code_t code = {};
    ReadByteCode(commands_file, stk, &code);

    for (size_t ip = 0; ip < code.size; ip++)
    {
        int cmd = (code.data)[ip];
        switch(cmd)
        {
            case CMD_PUSH:
            {
                StackPush(stk, (code.data)[ip + 1]);
                ip++;
                break;
            }
            case CMD_POP:
            {
                break;
            }
            case CMD_ADD:
            {
                StackElem_t value1 = 0;
                StackElem_t value2 = 0;
                StackPop(stk, &value1);
                StackPop(stk, &value2);
                StackPush(stk, value1 + value2);
                break;
            }
            case CMD_SUB:
            {
                StackElem_t value1 = 0;
                StackElem_t value2 = 0;
                StackPop(stk, &value2);
                StackPop(stk, &value1);
                StackPush(stk, value1 - value2);
                break;
            }
            case CMD_DIV:
            {
                StackElem_t value1 = 0;
                StackElem_t value2 = 0;
                StackPop(stk, &value2);
                StackPop(stk, &value1);
                StackPush(stk, value1 / value2);
                break;
            }
            case CMD_OUT:
            {
                StackElem_t value = 0;
                StackPop(stk, &value);
                fprintf(stdout, "The result is: %d\n", value);
                break;
            }
            case CMD_HLT:
            {
                ip = code.size;
                break;
            }
            default:
            {
                ip = code.size;
                break;
            }
        }
    }
}

int ReadByteCode(FILE* commands_file, Stack_t* stk, Code_t* code)
{
    if (commands_file == NULL)
    {
        fprintf(stderr, "%s(): failed to open commands file\n\n", __func__);
        return 1;
    }

    if (STACK_ASSERT_START(stk) != 0)
    {
        fprintf(stderr, "%s(): invalid stk\n\n", __func__);
        return 1;
    }

    char info[MAXLEN] = "";
    fscanf(commands_file, "%s", info);

    if (strcmp(info, "program_size:") != 0)
    {
        fprintf(stderr, "%s(): invalid commands file format\n\n", __func__);
        return 1;
    }

    int program_size = 0;
    fscanf(commands_file, "%d", &program_size);

    int* data = (int*) calloc(program_size, sizeof(int));

    for (int idx = 0; idx < program_size; idx++)
    {
        int cmd = 0;
        fscanf(commands_file, "%d", &cmd);
        data[idx] = cmd;

        if (cmd == CMD_PUSH)
        {
            int val = 0;
            fscanf(commands_file, "%d", &val);
            data[idx + 1] = val;
            idx++;
        }
    }

    code->data = data;
    code->size = program_size;

    return 0;
}
