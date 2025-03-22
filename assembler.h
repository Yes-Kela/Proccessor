#ifndef ASSEMBLER_H
#define ASSEMBLER_H

const int MAXCMD = 20;
const int MAX_PARAM = 1;

typedef struct
{
    const char* cmd_name;
    int cmd_code;
} Commands_t;

typedef struct
{
    int* cmdarr;                                                                    // int* -> StackElem_t
    size_t cmds_cap;                                                                // size_t -> StackSize_t
    size_t cmds_num;                                                                // size_t -> StackSize_t
} CmdArr_t;

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

int GetCommandCode(char* cmd);
int ReadAsm(FILE* program_file, CmdArr_t* tmp_code);
int MakeByteCode(FILE* commands_file, const CmdArr_t* tmp_code);
void AssemblerDump(const CmdArr_t* tmp_code);

#endif /* ASSEMBLER_H */
