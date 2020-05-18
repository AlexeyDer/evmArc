#include "mySimpleComputer.h"

int sc_memoryInit()
{
    for (int i = 0; i < N; i++)
    {
        memory[i] = 0x0;
    }

    return 0;
}

int sc_memorySet(int address, int value)
{
    if (address >= 0 && address < N)
    {
        sc_regSet(ERRORADD, 0);
        memory[address] = value;
        if (memory[address] == value)
        {
            return 0;
        }
    }
    sc_regSet(ERRORADD, 1);
    return ERRORADD;
}

int sc_memoryGet(int address, int *value)
{
    if (address >= 0 && address < N)
    {
        sc_regSet(ERRORADD, 0);
        *value = memory[address];
        return 0;
    }
    sc_regSet(ERRORADD, 1);
    return ERRORADD;
}

int sc_memorySave(char *filename)
{
    FILE *file;
    if (!(file = fopen(filename, "wb")))
    {
        sc_regSet(ERRORFILE, 1);
        return ERRORFILE;
    }
    fwrite(memory, sizeof(int), N, file);

    sc_regSet(ERRORFILE, 0);
    fclose(file);
    return 0;
}

int sc_memoryLoad(char *filename)
{
    FILE *file;

    if (!(file = fopen(filename, "rd")))
    {
        sc_regSet(ERRORFILE, 1);
        return ERRORFILE;
    }
    fread(memory, sizeof(int), N, file);

    fclose(file);
    sc_regSet(ERRORFILE, 0);
    return 0;
}

int sc_regInit(void)
{
    registr = registr & 0;

    return 0;
}

int sc_regSet(int flag, int value)
{
    if (flag >= 0 && flag < 32)
    {
        if (value == 0)
        {
            registr = registr & (~(1 << flag));
        }
        else if (value == 1)
        {
            registr = registr | (1 << flag);
        }
        else
        {
            return -1;
        }
        return 0;
    }

    sc_regSet(ERRORFLAG, 1);
    return ERRORFLAG;
}

int sc_regGet(int flag, int *value)
{
    if (flag >= 0 && flag < 31)
    {
        *value = (registr >> flag) & 0x1;
        return 0;
    }

    sc_regSet(ERRORFLAG, 1);
    return ERRORFLAG;
}

int sc_accumGet(int *value)
{
    *value = accumulator;
    return 0;
}

int sc_accumSet(int value)
{
    accumulator = value;
    return 0;
}

int sc_countGet(int *value)
{
    *value = instruction_counter;
    return 0;
}

int sc_countSet(int value)
{
    instruction_counter = value;
    return 0;
}

int sc_countInkrement()
{
    if (instruction_counter == N - 1)
        return -1;
    instruction_counter++;
    return 0;
}

int sc_checkCommand(int check_command)
{
    if (
        check_command == READ ||
        check_command == WRITE ||
        check_command == LOAD ||
        check_command == STORE ||
        check_command == ADD ||
        check_command == SUB ||
        check_command == DIVIDE ||
        check_command == MUL ||
        check_command == JUMP ||
        check_command == JNEG ||
        check_command == JZ ||
        check_command == HALT ||
        check_command == NOT ||
        check_command == AND ||
        check_command == OR ||
        check_command == XOR ||
        check_command == JNS ||
        check_command == JC ||
        check_command == JNC ||
        check_command == JP ||
        check_command == JNP ||
        check_command == CHL ||
        check_command == SHR ||
        check_command == RCL ||
        check_command == RCR ||
        check_command == NEG ||
        check_command == ADDC ||
        check_command == SUBC ||
        check_command == LOGLC ||
        check_command == LOGRC ||
        check_command == RCCL ||
        check_command == RCCR ||
        check_command == MOVA ||
        check_command == MOVR ||
        check_command == MOVCA ||
        check_command == MOVCR)
    {
        return 1;
    }
    return 0;
}

int sc_commandEncode(int command, int operand, int *value)
{
    if ((command > 0 && command < 10) ||
        (command > 11 && command < 20) ||
        (command > 21 && command < 30) ||
        (command > 33 && command < 40) ||
        (command > 44 && command < 51) ||
        command > 79)
    {
        sc_regSet(ERRORCOMS, 1);
        return 1;
    }

    if (operand < 0 || operand > 127)
    {
        sc_regSet(ERROROPER, 1);
        return 1;
    }

    *value = *value | (command << 7);
    *value = *value | operand;

    return 0;
}

int sc_commandDecode(int value, int *command, int *operand)
{
    if ((value >> 14) != 0)
    {
        sc_regSet(ERRORCOMS, 1);
        return 1;
    }

    *command = value >> 7;
    if ((*command > 0 && *command < 10) ||
        (*command > 11 && *command < 20) ||
        (*command > 21 && *command < 30) ||
        (*command > 33 && *command < 40) ||
        (*command > 44 && *command < 51) ||
        *command > 79)
    {
        sc_regSet(ERRORCOMS, 1);
        return 1;
    }

    *operand = value & 0x7;

    return 0;
}

// int commands[] = {
//     0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32,
//     0x33, 0x40, 0x41, 0x42, 0x43, 0x51, 0x52,
//     0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
//     0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
//     0x67, 0x68, 0x69, 0x70, 0x71, 0x72, 0x73,
//     0x74, 0x75, 0x76};

// int sc_commandDecode(int value, int *command, int *operand)
// {
//     int buf = 0;
//     int attribute;
//     int buf_command;
//     int buf_operand;

//     attribute = (value >> 14) & 1;
//     if (attribute == 0)
//     {
//         buf_command = (value >> 7) & 0x7F;
//         buf_operand = value & 0x7F;

//         for (int i = 0; i < 37; i++)
//         {
//             if (buf_command == commands[i])
//             {
//                 buf = 1;
//             }
//         }

//         if ((buf == 1) && ((*operand >= 0) && (*operand < N)))
//         {
//             *command = buf_command;
//             *operand = buf_operand;
//         }
//         else if (buf == 0)
//         {
//             return -1;
//         }
//         return 0;
//     }
//     else
//     {
//         return -1;
//     }
// }
