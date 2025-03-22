/* assembler */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembler.h"

int AssembleProgram(FILE* program_file)                                             // todo: what is returned value?
{
    FILE* commands_file = fopen("commands.txt", "w");
    if (commands_file == NULL)
    {
        fprintf(stdout, "An error occured while opening commands file\n");
        fprintf(stdout, "We must stop the program\n");                              // todo: error-message into err-file
        return 1;
    }

    char cmd[MAXCMD] = "";
    while (fscanf(program_file, "%s", cmd) != EOF)
    {
        int cmd_code = GetCommandCode(cmd);
        if (cmd_code == CMD_PUSH)
        {
            int val = 0;
            fscanf(program_file, "%d", &val);
            fprintf(commands_file, "%d %d\n", cmd_code, val);
        }
        else
        {
            fprintf(commands_file, "%d\n", cmd_code);
        }
    }

    fclose(commands_file);

    return 0;
}

int GetCommandCode(char* cmd)
{
    size_t cmd_number = sizeof(commands) / sizeof(commands[0]);

    for (size_t i = 0; i < cmd_number; i++)
    {
        if (!strcmp(cmd, commands[i].cmd_name))
        {
            return commands[i].cmd_code;
        }
    }

    return 0;
}
