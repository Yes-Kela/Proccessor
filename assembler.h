#ifndef ASSEMBLER_H
#define ASSEMBLER_H

const int MAXCMD = 20;
typedef struct
{
    const char* cmd_name;
    int cmd_code;
} Commands_t;

enum CmdCodes
{
    CMD_PUSH = 1,
    CMD_POP  = 2,
    CMD_ADD  = 3,
    CMD_SUB  = 4,
    CMD_DIV  = 5,
    CMD_MUL  = 6,
    CMD_IN   = 7,
    CMD_OUT  = 8,
    CMD_HLT  = 9
};

Commands_t commands[] =
{
    {"push", CMD_PUSH},
    {"pop",  CMD_POP},
    {"add",  CMD_ADD},
    {"sub",  CMD_SUB},
    {"div",  CMD_DIV},
    {"mul",  CMD_MUL},
    {"in",   CMD_IN},
    {"out",  CMD_OUT},
    {"hlt",  CMD_HLT}
};

int AssembleProgram(FILE* program_file);
int GetCommandCode(char* cmd);

#endif /* ASSEMBLER_H */
