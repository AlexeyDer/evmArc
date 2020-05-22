#include "cpu.h"

int ALU(int command, int operand)
{
    if (operand > 99)
    {
        return 1;
    }

    switch (command)
    {
    case ADD:
        if ((accumulator + memory[operand]) >= 65535)
        {
            sc_regSet(OD, 1);
            break;
        }
        accumulator += memory[operand];
        break;
    case SUB:
        if ((accumulator - memory[operand]) < -65534)
        {
            sc_regSet(OD, 1);
            break;
        }
        accumulator -= memory[operand];
        break;
    case DIVIDE:
        if (memory[operand] == 0 || accumulator == 0)
        {
            sc_regSet(DE, 1);
            break;
        }
        accumulator /= memory[operand];
        break;
    case MUL:
        if ((accumulator * memory[operand]) >= 65535)
        {
            sc_regSet(OD, 1);
            break;
        }
        accumulator *= memory[operand];
        break;
    default:
        return 1;
    }

    return 0;
}

int CU(void)
{
    int command, operand;
    int value;

    sc_memoryGet(pointer_mem, &value);
    if (!sc_commandDecode(value, &command, &operand))
    {
        sc_regSet(ERRORFLAG, 1);
        return 1;
    }
    sc_accumSet(command);
    command += 7;

    value = 0;

    if (command < 30 || command > 33)
    {
        switch (command)
        {
        case READ:
        {
            int n, m;
            mt_getscreensize(&n, &m);
            int x = n / 3 + STD_DX_MEM + 10, y = m / 4 + 2;

            mt_gotoXY(x, y);
            mt_setfgcolor(RED);
            printf("I");
            mt_gotoXY(x + 1, y);
            mt_setfgcolor(WHITE);
            printf(":");
            mt_gotoXY(x + 1, y + 1);
            mt_setbgcolor(BLACK);

            int value;
            fscanf(stdin, "%x", &value); //

            if (value > 65535)
            {
                sc_regSet(ERRORADD, 1);
                break;
            }

            // sc_accumSet(value);
            sc_memorySet(operand, value);
            mt_setbgcolor(BLACK);
            clrMessageBox(x, y);
            setVisualNull();
        }
        break;
        case WRITE:
        {
            int n, m;
            mt_getscreensize(&n, &m);
            int x = n / 3 + STD_DX_MEM + 10, y = m / 4 + 2;

            mt_gotoXY(x, y);
            mt_setfgcolor(RED);
            printf("O");
            mt_gotoXY(x + 1, y);
            mt_setfgcolor(WHITE);
            printf(":");

            mt_gotoXY(x + 1, y + 1);
            mt_setbgcolor(BLACK);
            printf("%d\n", memory[operand]);
            break;
        }
        case LOAD:
            sc_accumSet(memory[operand]);
            break;
        case STORE:
            sc_accumGet(&memory[operand]);
            break;

        case JUMP:
            if (operand > 99 || operand < 0)
            {
                sc_regSet(EG, 1);
                break;
            }
            instruction_counter = operand;
            instruction_counter--;
            break;
        case JNEG:
            if (accumulator < 0)
            {
                instruction_counter = operand;
                instruction_counter--;
            }
            break;
        case JZ:
            if (accumulator == 0)
            {
                instruction_counter = operand;
                instruction_counter--;
            }
            break;
        case JC:
            sc_regGet(OD, &value);
            if (value == 1)
            {
                instruction_counter = operand;
                instruction_counter--;
            }
            break;
        case JB:
            if (accumulator > 0)
            {
                instruction_counter = operand;
                instruction_counter--;
            }
            break;

        case SET:
            accumulator = operand;
            break;

        case HALT:
            return 2;
            break;
        default:
            if (command == 0)
                sc_regSet(ERRORFILE, 1);
            break;
        }
    }
    else
    {
        if (ALU(command, operand))
        {
            return 1;
        }
    }

    return 0;
}
