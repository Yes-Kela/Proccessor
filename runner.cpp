/* runner */
#include <stdio.h>
#include "stack.h"
#include "runner.h"

void RunProgram(FILE* commands_file, Stack_t* stk)
{
    int next = 1;
    while (next)
    {
        int cmd = 0;
        fscanf(commands_file, "%d", &cmd);

        switch(cmd)
        {
            case CMD_PUSH:
            {
                StackElem_t value = 0;
                fscanf(commands_file, "%d", &value);
                StackPush(stk, value);
                break;
            }
            //case CMD_POP:
            case CMD_ADD:
            {
                StackElem_t value1 = 0;
                StackElem_t value2 = 0;
                //STACK_POP(&value2);
                StackPop(stk, &value2);
                StackPop(stk, &value1);
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
                next = 0;
                break;
            }
            default:
            {
                next = 0;
                break;
            }
        }
    }
}
