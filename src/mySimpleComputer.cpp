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
        return 1;
    }

    if (operand < N)
    {
        sc_regSet(ERRORCOMS, 0);
        *value = (command << 7) | operand;
        return 0;
    }
    sc_regSet(ERRORCOMS, 1);
    return ERRORCOMS;
}

int sc_commandDecode(int value, int *command, int *operand)
{
    int buffer;
    buffer = (value >> 7) & 0x7F;
    if ((value >> 14) != 0)
    {
        sc_regSet(ERRORCOMS, 1);
        return ERRORCOMS;
    }
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

    sc_regSet(ERRORCOMS, 0);
    *command = buffer;
    buffer = value & 0x7;
    if (buffer < 100)
    {
        *operand = buffer;
    }
    else
    {
        *command = -1;
        *operand = -1;
        sc_regSet(ERRORCOMS, 1);
        return ERROROPER;
    }
    return 0;
}
