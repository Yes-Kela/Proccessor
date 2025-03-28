/* runner */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "stack.h"
#include "runner.h"

void RunProgram(FILE* commands_file, Stack_t* stk)
{
    Code_t code = {};
    ReadByteCode(commands_file, &code);

    RunByteCode(stk, &code);
}

int ReadByteCode(FILE* commands_file, Code_t* code)
{
    if (commands_file == NULL)
    {
        fprintf(stderr, "%s(): failed to open commands file\n\n", __func__);
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

int RunByteCode(Stack_t* stk, Code_t* code)
{
    if (STACK_ASSERT_START(stk) != 0)
    {
        fprintf(stderr, "%s: %s(): invalid stk\n", __FILE__, __func__);
        return 1;
    }

    if (code == NULL)
    {
        fprintf(stderr, "%s: %s(): invalid code ptr\n", __FILE__, __func__);
        return 1;
    }

    if (code->size >= MAX_CODE_SIZE)
    {
        fprintf(stderr, "%s: %s(): invalid code size\n", __FILE__, __func__);
        return 1;
    }

    if (code->data == NULL)
    {
        fprintf(stderr, "%s: %s(): invalid code data ptr\n", __FILE__, __func__);
        return 1;
    }

    ProcDump(stk);

    for (size_t ip = 0; ip < code->size; ip++)
    {
        int cmd = (code->data)[ip];
        switch(cmd)
        {
            case CMD_PUSH:
            {
                StackPush(stk, (code->data)[ip + 1]);
                ProcDump(stk);
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
                ProcDump(stk);

                StackPop(stk, &value2);
                ProcDump(stk);

                StackPush(stk, value1 + value2);
                ProcDump(stk);

                break;
            }
            case CMD_SUB:
            {
                StackElem_t value1 = 0;
                StackElem_t value2 = 0;

                StackPop(stk, &value2);
                ProcDump(stk);

                StackPop(stk, &value1);
                ProcDump(stk);

                StackPush(stk, value1 - value2);
                ProcDump(stk);

                break;
            }
            case CMD_DIV:
            {
                StackElem_t value1 = 0;
                StackElem_t value2 = 0;

                StackPop(stk, &value2);
                ProcDump(stk);

                StackPop(stk, &value1);
                ProcDump(stk);

                StackPush(stk, value1 / value2);
                ProcDump(stk);

                break;
            }
            case CMD_OUT:
            {
                StackElem_t value = 0;

                StackPop(stk, &value);
                ProcDump(stk);

                fprintf(stdout, "The result is: %d\n", value);
                break;
            }
            case CMD_HLT:
            {
                ip = code->size;
                break;
            }
            default:
            {
                ip = code->size;
                break;
            }
        }
    }

    return 0;
}


// TODO: returned value of RunByteCode()
// TODO: make errors processing and good CodeDump() AND rewrite StackDump()
// TODO: think about two or more modes for Dump()
// TODO: make registers and labels!


void ProcDump(const Stack_t* stk/*, const Code_t* code, const char* file_name, const char* func_name, const int line*/)
{
    fprintf(stderr, "StackUsage:\n");
    fprintf(stderr, "   stk = [%p]\n", stk);
    if (stk != NULL)
    {
        fprintf(stderr, "   stk.capacity = %u  |  stk.size = %u  |  stk.data = [%p]\n",
                            stk->capacity,        stk->size,        stk->data);

        if (stk->data != NULL)
        {
            fprintf(stderr, "   stack: ");

            StackCanary_t left_canary = GetLeftCanary(stk);
            fprintf(stderr, "0x%lX  ", left_canary);

            for (size_t idx = 0; idx < stk->capacity; idx++)
            {
                StackElem_t val = GetStackElem(stk, idx);
                if ((StackElem_t) val == (StackElem_t) SPOILED)
                {
                    fprintf(stderr, "0x%X  ", val);
                }
                else
                {
                    fprintf(stderr, "%5u  ", val);
                }
            }

            StackCanary_t right_canary = GetRightCanary(stk);
            fprintf(stderr, "0x%lX  ", right_canary);

            fprintf(stderr, "\n");
        }
    }

    /*
    fprintf(stderr, "CodeUsage:\n");
    fprintf(stderr, "   code = [%p]\n", code);
    if (code != NULL)
    {
        fprintf(stderr, "   code.size = %u  |  code.data = [%p]\n",
                            code->size,        code->data);
        if (code->data != NULL)
        {
            fprintf(stderr, "   code: ");
            for (size_t ip = 0; ip < code->size; ip++)
            {
                fprintf(stderr, "%5u  ", code->data[ip]);
            }
            fprintf(stderr, "\n");
        }
    }
    */
    fprintf(stderr, "\n");
}
