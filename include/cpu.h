#ifndef CPU_H
#define CPU_H

#define READ 10
#define WRITE 11

#define LOAD 20
#define STORE 21

#define ADD 30
#define SUB 31
#define DIVIDE 32
#define MUL 33

#define JUMP 40
#define JNEG 41
#define JZ 42
#define JNS 55
#define SET 78
#define HALT 43

int ALU(int command, int operand);
int CU(void);

#endif