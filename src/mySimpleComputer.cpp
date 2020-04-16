#include "mySimpleComputer.h"

int instruction_counter;
int accumulator;
int registr;

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

int commands[] = {
    0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32,
    0x33, 0x40, 0x41, 0x42, 0x43, 0x51, 0x52,
    0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
    0x67, 0x68, 0x69, 0x70, 0x71, 0x72, 0x73,
    0x74, 0x75, 0x76};

void printMemory()
{
    for (int i = 0; i < 100; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int printFlag(int flag)
{
    int val = 2;
    return sc_regGet(flag, &val);
}

int sc_memoryInit()
{
    for (int i = 0; i < 100; i++)
    {
        a[i] = 0;
    }
    return 0;
}

int sc_memorySet(int address, int value)
{
    if (address < 0 || address > 100)
    {
        sc_regSet(ERROROUTOFMEMORY, 1);
        // cout << "ошибка выхода за границы памяти" << endl;
        return -1;
    }
    a[address] = value;
    return 0;
}

int sc_memoryGet(int address, int *value)
{
    if (address < 0 || address > 100)
    {
        sc_regSet(ERROROUTOFMEMORY, 1);
        // cout << "ошибка выхода за границы памяти" << endl;
        return -1;
    }
    sc_regSet(ERROROUTOFMEMORY, 0);
    return *value = a[address];
}

int sc_memorySave(char *filename)
{
    FILE *in = fopen(filename, "w+b");
    if (in == NULL)
    {
        sc_regSet(ERRORFILE, 1);
        return -1;
    }
    sc_regSet(ERRORFILE, 1);
    for (int i = 0; i < 100; i++)
    {
        fwrite(&a[i], sizeof(int), 1, in);
    }
    fclose(in);
    return 0;
}

int sc_memoryLoad(char *filename)
{
    FILE *out = fopen(filename, "rb");
    if (out == NULL)
    {
        sc_regSet(ERRORFILE, 1);
        return -1;
    }
    sc_regSet(ERRORFILE, 1);
    for (int i = 0; i < 100; i++)
    {
        fread(a, sizeof(a), 1, out);
    }
    fclose(out);
    return 0;
}

int sc_regInit(void)
{
    flag = 0;
    return 0;
}

int sc_regSet(int reg, int value)
{
    if (value < 0 || value > 1)
    {
        // cout << "ошибка выхода за границы знчения регистра" << endl;
        sc_regSet(ERROROUTOFMEMORY, 1);
        return -1;
    }
    if (reg < 0 || reg > 5)
    {
        sc_regSet(ERRORFLAG, 1);
        // cout << "ошибка выхода за границы возможных флагов" << endl;
        return -1;
    }
    if (value == 1)
    {
        flag = flag | (1 << (reg - 1));
    }
    else
    {
        flag = flag & (~(1 << (reg - 1)));
    }
    return 0;
}

int sc_regGet(int reg, int *value)
{
    if (reg < 0 || reg > 5)
    {
        sc_regSet(ERRORFLAG, 1);
        // cout << "ошибка выхода за границы возможных флагов" << endl;
        return -1;
    }
    sc_regSet(ERRORFLAG, 0);
    return *value = (flag >> (reg - 1)) & 0x1;
}

int sc_commandEncode(int command, int operand, int *value)
{

    for (int i = 0; i < 37; i++)
    {
        if (commands[i] == command)
        {
            sc_regSet(ERRORCOMS, 0);
            return *value = (command & 0x7F) << 7 | (operand & 0x7F);
        }
    }
    sc_regSet(ERRORCOMS, 1);
    return -1;
}

int sc_commandDecode(int value, int *command, int *operand)
{
    if (value >> 14 == 0)
    {
        *command = (value >> 7) & 0x7F;
        for (int i = 0; i < 37; i++)
        {
            if (commands[i] == *command)
            {
                sc_regSet(ERRORCOMS, 0);
                *command = (value >> 7) & 0x7F;
                if (operand != NULL)
                {
                    *operand = value & 0x7F;
                }
                else
                {
                    sc_regSet(ERRORCOMS, 1);
                    return -1;
                }
                return 0;
            }
        }
    }

    return -1;
}