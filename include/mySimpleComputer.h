#ifndef MYSIMPLECOMPUTER_H
#define MYSIMPLECOMPUTER_H
#include <stdio.h>
#define N 100
#define M 10

#define ERRORADD 1
#define ERRORFLAG 2
#define ERRORFILE 3
#define ERRORCOMS 4
#define ERROROPER 5
#define IGNOREPULSE 6

extern int memory[N];
extern int registr;
extern int instruction_counter, accumulator;
extern int pointer_mem;

#define OD 0b00000001 // переполнение при выполнении операции
#define DE 0b00000010 // ошибка деления на 0
#define EG 0b00000100 // ошибка выхода за границы памяти
#define CI 0b00001000 // игнорирование тактовых импульсов
#define IC 0b00010000 // неверная команда

// Memory //

int sc_memoryInit();

int sc_memorySet(int address, int value);

int sc_memoryGet(int address, int *value);

int sc_memorySave(char *filename);

int sc_memoryLoad(char *filename);

// Register //

int sc_regInit(void);

int sc_regSet(int flag, int value);

int sc_regGet(int flag, int *value);

int sc_commandEncode(int command, int operand, int *value);

int sc_commandDecode(int value, int *command, int *operand);

#endif