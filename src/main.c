#include "../include/myConsole.h"
#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"
#include "../include/myReadKey.h"
#include "../include/myBigChar.h"
#include "../include/cpu.h"

int main()
{
    sc_memoryInit();
    sc_regInit();

    enum Key key = NONE;
    int value;
    mt_setbgcolor(BLACK);

    sc_regSet(IGNOREPULSE, 0);

    termInit();
    signal(SIGALRM, run);
    signal(SIGUSR1, reset);
    settimer(&nval);

    sc_memoryLoad("output.o");

    while (key != EXIT)
    {
        mt_clrscr();
        fflush(stdout);
        setVisualNull();
        showAll();
        sc_regGet(IGNOREPULSE, &value);

        if (!value)
        {
            rk_readKey(&key);
            switch (key)
            {
            case UP:
                pointer_mem -= 10;
                if (pointer_mem < 0)
                {
                    pointer_mem += N;
                }
                updateMemVisual();
                break;

            case DOWN:
                pointer_mem += 10;
                if (pointer_mem > N - 1)
                {
                    pointer_mem -= N;
                }
                updateMemVisual();
                break;

            case LEFT:
                pointer_mem--;
                if (pointer_mem < 0)
                {
                    pointer_mem = N - 1;
                }
                updateMemVisual();
                break;
            case RIGHT:
                pointer_mem++;
                if (pointer_mem > N - 1)
                {
                    pointer_mem = 0;
                }
                updateMemVisual();
                break;
            case SAVE:
                sc_memorySave("memory.dat");
                break;
            case KLOAD:
                sc_memoryLoad("memory.dat");
                break;
            case F5:
                setAcc();
                break;
            case F6:
                setPointer();
                break;
            case RESET:
                raise(SIGUSR1);
                break;
            case RUN:
                sc_regSet(IGNOREPULSE, 1);
                pointer_mem = 0;
                break;
            case STEP:
                CU();
                pointer_mem++;
                break;
            case ENTER:
                setOperation();
                break;
            default:
                break;
            }
        }
        else
        {
            setitimer(ITIMER_REAL, &nval, NULL);
            pause();
        }
    }

    rk_myTermRestore();
    mt_gotoXY(60, 1);
    return 0;
}
