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
#define IGNORTACT 6

static int memory[N];
static int registr;
static int instruction_counter;
static int accumulator;

#define OD 0b00000001 // переполнение при выполнении операции
#define DE 0b00000010 // ошибка деления на 0
#define EG 0b00000100 // ошибка выхода за границы памяти
#define CI 0b00001000 // игнорирование тактовых импульсов
#define IC 0b00010000 // неверная команда

// Memory //

int sc_memoryInit(); // Initialization array memory

int sc_memorySet(int address, int value); // Set value to address

int sc_memoryGet(int address, int *value); // Get value of address

int sc_memorySave(char *filename); // Save to file in binary view

int sc_memoryLoad(char *filename); // Load of file RAM

// Register //

int sc_regInit(void); // It initializaion register of flags zero value

int sc_regSet(int flag, int value); // sets the value of the flag register

int sc_regGet(int flag, int *value); // gets the value of the flag

int sc_commandEncode(int command, int operand, int *value); // encodes a command with the specified number and operand and put result in Value

int sc_commandDecode(int value, int *command, int *operand); // decodes the value that command SC

//

int sc_accumGet(int *value);

int sc_accumSet(int value);

int sc_countGet(int *value);

int sc_countSet(int value);

int sc_countInkrement();

#endif
