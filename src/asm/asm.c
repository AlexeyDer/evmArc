#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int getCommand(char *cmd)
{
    if (!strcmp(cmd, "READ"))
        return 10;
    if (!strcmp(cmd, "WRITE"))
        return 11;
    if (!strcmp(cmd, "LOAD"))
        return 20;
    if (!strcmp(cmd, "STORE"))
        return 21;
    if (!strcmp(cmd, "ADD"))
        return 30;
    if (!strcmp(cmd, "SUB"))
        return 31;
    if (!strcmp(cmd, "DIVIDE"))
        return 32;
    if (!strcmp(cmd, "MUL"))
        return 33;
    if (!strcmp(cmd, "JUMP"))
        return 40;
    if (!strcmp(cmd, "JNEG"))
        return 41;
    if (!strcmp(cmd, "JZ"))
        return 42;
    if (!strcmp(cmd, "HALT"))
        return 43;
    if (!strcmp(cmd, "="))
        return 99;
    return -1;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("2 arguments needed\nsat <inputFile.sa> <outputFile.o>\n");
        return -1;
    }
    char *p = strrchr(argv[1], '.');
    if (p == NULL || strlen(argv[1]) <= 3 || strcmp(p, ".sa") != 0)
        printf("FIRST ARG ERROR\n");
    p = strrchr(argv[2], '.');
    if (p == NULL || strlen(argv[2]) <= 2 || strcmp(p, ".o") != 0)
        printf("SECOND ARG ERROR\n");

    FILE *input, *output;

    if ((input = fopen(argv[1], "r")) == NULL)
        printf("FIRST FILE ERROR");
    if ((output = fopen(argv[2], "wb+")) == NULL)
        printf("SECOND FILE ERROR");

    while (!feof(input))
    {
        int a, b;
        char str[10], in[3], out[10], s[1024];
        fgets(s, 1024, input);
        int check = sscanf(s, "%s %s %s ", in, str, out);
        if (check != 3 || strlen(in) != 2 || !(strlen(out) == 2 || strlen(out) == 5))
        {
            printf("ERROR WRONG INPUT %s %s %s \n", in, str, out);
            break;
        }

        for (int i = 0; i < strlen(in); i++)
            if (!(in[i] >= '0' && in[i] <= '9'))
            {
                printf("ERROR FIRST ARGUMENT INPUT\n");
                break;
            }
        if (strlen(out) == 2)
        {
            if (strcmp(str, "=") == 0)
            {
                printf("ERROR WRONG EQUEL\n");
                break;
            }
            for (int i = 0; i < strlen(out); i++)
                if (!(out[i] >= '0' && out[i] <= '9'))
                {
                    printf("ERROR WRONG OUT1\n");
                    break;
                }
        }
        else
        {
            if (strcmp(str, "=") != 0)
            {
                printf("ERROR DONT FIND EQUEL\n");
                break;
            }
            if (out[0] != '+')
            {
                printf("ERROR NOT FIND +\n");
                break;
            }
            for (int i = 1; i < strlen(out); i++)
                if (!((out[i] >= '0' && out[i] <= '9') || (out[i] >= 'A' && out[i] <= 'F')))
                {
                    printf("ERROR WRONT OUT2\n");
                    break;
                }
        }
        if (strlen(str) == 1)
        {
            if (str[0] != '=')
            {
                printf("ERROR EQUEL COMMAND\n");
                break;
            }
        }

        else if (getCommand(str) == -1)
        {
            printf("ERROR COMMAND\n");
            break;
        }

        /*char* ch = strchr(s,';');
		if(ch==NULL){printf("ERROR NO COMMENT\n");break;}*/
        a = atoi(in);
        if (strlen(out) == 5)
        {
            b = (int)strtol(out, NULL, 16);
            if (b < 0x0000 || b > 0x3fff)
            {
                printf("ERROR WRONG NUMBER\n");
                break;
            }
        }
        else
            b = atoi(out);
        int data[3];
        data[0] = a;
        data[1] = getCommand(str);
        data[2] = b;

        fwrite(data, sizeof(int) * 3, 1, output);
    }

    fclose(input);
    fclose(output);

    return 0;
}