#ifndef ASM_H
#define ASM_H

#include <stdio.h>
#include <string.h>

#include "mySimpleComputer.h"

#define ERR_ARG1 -1
#define ERR_ARG2 -2
#define ERR_ARG3 -3
#define ERR_FEW -4
#define ERR_MANY -5
#define EMPTY_STR 1

int str2sc_word(char *str, int *value);
int getCommand(char *str);
int parsingLine(char *str, int *addr, int *value);
void print_error(char *line, int line_cnt, int err);
int test_argv(char *argv[]);
int main(int argc, char *argv[]);

#endif /* __GUARD_SAT_H */