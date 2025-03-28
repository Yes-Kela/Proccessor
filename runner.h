#ifndef RUNNER_H
#define RUNNER_H

#define MAX_CODE_SIZE SIZE_MAX - 2

const int MAXLEN = 100;


typedef struct
{
    const char* cmd_name;
    int cmd_code;
} Commands_t;

typedef struct
{
    int* data;
    size_t size;
} Code_t;

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

void RunProgram(FILE* commands_file, Stack_t* stk);
int ReadByteCode(FILE* commands_file, Code_t* code);
int RunByteCode(Stack_t* stk, Code_t* code);

void ProcDump(const Stack_t* stk/*, const Code_t* code*/);

#endif /* RUNNER_H */
