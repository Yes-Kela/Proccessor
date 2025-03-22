/* assembler */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "assembler.h"

int main(void)
{
    FILE* asmbl_err_file = fopen("asmbl_errors.txt", "w");

    if (asmbl_err_file == NULL)
    {
        fprintf(stderr, "failed to open asmbl_errors file\n");
        return 1;
    }

    asmbl_err_file = freopen("asmbl_errors.txt", "w", stderr);

    fprintf(stderr, "ABRAKADABRA\n");

    FILE* program_file = fopen("program.txt", "r");
    if (program_file == NULL)
    {
        fprintf(stderr, "failed to open program file\n");
        return 1;
    }

    size_t cmds_cap = 5;

    int* cmdarr = (int*) calloc(cmds_cap, sizeof(int));                             // int -> StackElem_t
    if (cmdarr == NULL)
    {
        fprintf(stderr, "failed to alloc memory for cmdarr\n");
        return 0;
    }

    CmdArr_t tmp_code = {cmdarr, cmds_cap, 0};
    AssemblerDump(&tmp_code);

    ReadAsm(program_file, &tmp_code);
    AssemblerDump(&tmp_code);

    FILE* commands_file = fopen("commands.txt", "w");
    if (commands_file == NULL)
    {
        fprintf(stderr, "failed to open commands file\n");
        fclose(program_file);
        return 1;
    }

    MakeByteCode(commands_file, &tmp_code);
    AssemblerDump(&tmp_code);

    free(cmdarr);
    cmdarr = NULL;

    fclose(commands_file);
    fclose(program_file);
    fclose(asmbl_err_file);

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

int ReadAsm(FILE* program_file, CmdArr_t* tmp_code)
{
    char cmd[MAXCMD] = "";

    while (fscanf(program_file, "%s", cmd) != EOF)
    {
        AssemblerDump(tmp_code);

        if (tmp_code->cmds_num >= tmp_code->cmds_cap - MAX_PARAM)
        {
            tmp_code->cmds_cap *= 2;
            tmp_code->cmdarr = (int*) realloc(tmp_code->cmdarr, (size_t) tmp_code->cmds_cap);
        }

        int cmd_code = GetCommandCode(cmd);
        if (cmd_code == CMD_PUSH)
        {
            int val = 0;
            fscanf(program_file, "%d", &val);
            (tmp_code->cmdarr) [tmp_code->cmds_num] = cmd_code;
            (tmp_code->cmdarr) [tmp_code->cmds_num + 1] = val;
            tmp_code->cmds_num += 2;
        }
        else
        {
            (tmp_code->cmdarr) [tmp_code->cmds_num] = cmd_code;
            tmp_code->cmds_num++;
        }
    }

    return 0;
}

int MakeByteCode(FILE* commands_file, const CmdArr_t* tmp_code)
{

    for (size_t i = 0; i < tmp_code->cmds_num; i++)
    {
        if ((tmp_code->cmdarr)[i] == CMD_PUSH)
        {
            fprintf(commands_file, "%d %d\n", (tmp_code->cmdarr)[i], (tmp_code->cmdarr)[i + 1]);
            i++;
        }
        else
        {
            fprintf(commands_file, "%d\n", (tmp_code->cmdarr)[i]);
        }
    }

    return 0;
}


void AssemblerDump(const CmdArr_t* tmp_code)
{
    fprintf(stderr, "tmp_code = [%p]\n", tmp_code);

    if (tmp_code != NULL)
    {
        fprintf(stderr, "tmp_code = {cmdarr = %p, cmds_cap = %d, cmds_num = %d}\n", tmp_code->cmdarr, tmp_code->cmds_cap, tmp_code->cmds_num);
        if (tmp_code->cmdarr != NULL)
        {
            for (size_t i = 0; i < tmp_code->cmds_num; i++)
            {
                fprintf(stderr, "    cmdarr[%d] = %d\n", i, tmp_code->cmdarr[i]);
            }
        }
    }

    fprintf(stderr, "\n\n");
}
