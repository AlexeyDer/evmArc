#include "../include/asm.h"

int str2sc_word(char *str, int *value)
{
    int position = 0, plus = 1;
    int n;
    int byte1, byte2;

    if (str[0] == '+')
    {
        plus = 0;
        position = 1;
    }
    if (sscanf(str + position, "%x", &n) != 1)
        return -1;
    byte1 = n & 0xFF;
    byte2 = n >> 8;
    if ((byte1 > 0x7F) || (byte2 > 0x7F))
        return -1;
    *value = byte1 | (byte2 << 7) | (plus << 14);
    return 0;
}

int getCommand(char *str)
{
    if (strcmp(str, "READ") == 0)
        return 10;
    else if (strcmp(str, "WRITE") == 0)
        return 11;
    else if (strcmp(str, "LOAD") == 0)
        return 20;
    else if (strcmp(str, "STORE") == 0)
        return 21;
    else if (strcmp(str, "ADD") == 0)
        return 30;
    else if (strcmp(str, "SUB") == 0)
        return 31;
    else if (strcmp(str, "DIVIDE") == 0)
        return 32;
    else if (strcmp(str, "MUL") == 0)
        return 33;
    else if (strcmp(str, "JUMP") == 0)
        return 40;
    else if (strcmp(str, "JNEG") == 0)
        return 41;
    else if (strcmp(str, "JZ") == 0)
        return 42;
    else if (strcmp(str, "HALT") == 0)
        return 43;
    else if (strcmp(str, "JNS") == 0)
        return 55;
    else
        return -1;
}

int parsingLine(char *str, int *addr, int *value)
{
    char *ptr;
    int operand, command;
    int flag_assign = 0;

    ptr = strchr(str, ';');
    if (ptr != NULL)
        *ptr = '\0';
    ptr = strchr(str, '\n');
    if (ptr != NULL)
        *ptr = '\0';
    ptr = strtok(str, " \t");
    if (ptr == NULL)
        return EMPTY_STR;
    if (sscanf(ptr, "%d", addr) != 1)
    {
        return ERR_ARG1;
    }
    if ((*addr < 0) || (*addr >= N))
        return ERR_ARG1;
    ptr = strtok(NULL, " \t");
    if (ptr == NULL)
        return ERR_FEW;
    else if (strcmp(ptr, "=") == 0)
        flag_assign = 1;
    else
    {
        command = getCommand(ptr);
        if (command == -1)
            return ERR_ARG2;
    }
    ptr = strtok(NULL, " \t");
    if (ptr == NULL)
        return ERR_FEW;
    if (!flag_assign)
    {
        if (sscanf(ptr, "%d", &operand) != 1)
        {
            return ERR_ARG3;
        }
    }
    else
    {
        if (str2sc_word(ptr, value) == -1)
        {
            return ERR_ARG3;
        }
    }
    if ((operand < 0) || (operand >= N))
        return ERR_ARG3;
    ptr = strtok(NULL, " \t");
    if (ptr != NULL)
        return ERR_MANY;
    if (!flag_assign)
    {
        sc_commandEncode(command, operand, value);
    }
    return 0;
}

void printError(char *line, int line_cnt, int err)
{
    switch (err)
    {
    case ERR_ARG1:
        fprintf(stderr, "%d: first argument isn't a number\n", line_cnt);
        break;

    case ERR_ARG2:
        fprintf(stderr, "%d: unknown command\n", line_cnt);
        break;

    case ERR_ARG3:
        fprintf(stderr, "%d: third argument isn't a number\n", line_cnt);
        break;

    case ERR_FEW:
        fprintf(stderr, "%d: should be three aguments\n", line_cnt);
        break;

    case ERR_MANY:
        fprintf(stderr, "%d: too many arguments\n", line_cnt);
        break;
    }
    fprintf(stderr, "%s", line);
}

int test_argv(char *argv[])
{
    char *ptr1, *ptr2;

    ptr1 = strrchr(argv[1], '.');
    ptr2 = strrchr(argv[2], '.');
    if ((strcmp(ptr1, ".o") != 0) || (strcmp(ptr2, ".sa") != 0))
        return -1;
    else
        return 0;
}

int main(int argc, char *argv[])
{
    char buf[256], line[256];
    char add_mem[N];
    FILE *input, *output;
    int value, addr, line_cnt = 1;
    int error;
    int flag_err = 0;

    if (argc != 3)
    {
        perror("Incorrect arguments!\n");
        return 1;
    }
    if (test_argv(argv) != 0)
    {
        perror("Incorrect arguments!\n");
        return 1;
    }
    if ((output = fopen(argv[1], "wb")) == NULL)
    {
        fprintf(stderr, "Cannot open file:%s", argv[1]);
        return 1;
    }
    if ((input = fopen(argv[2], "rb")) == NULL)
    {
        fprintf(stderr, "Cannot open file:%s", argv[2]);
        return 1;
    }

    memset(add_mem, 0, N);
    memset(memory, 0, N * sizeof(int));
    while (fgets(line, 256, input))
    {
        strcpy(buf, line);
        error = parsingLine(buf, &addr, &value);
        if (error == 0)
        {
            if (add_mem[addr] == 0)
            {
                memory[addr] = value;
            }
            else
            {
                fprintf(stderr, "%d: Command with %d addres already exists\n%s", line_cnt, addr, line);
                flag_err = 1;
            }
        }
        else if (error < 0)
        {
            printError(line, line_cnt, error);
            flag_err = 1;
        }
        line_cnt++;
    }
    if (flag_err == 0)
    {
        fwrite(memory, 1, N * sizeof(int), output);
    }
    fclose(input);
    fclose(output);
    return 0;
}