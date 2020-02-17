#include "mySimpleComputer.h"

int commands[] = { 	
0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32,
0x33, 0x40, 0x41, 0x42, 0x43, 0x51, 0x52,
0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59,
0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 
0x67, 0x68, 0x69, 0x70, 0x71, 0x72, 0x73, 
0x74, 0x75, 0x76
};

void printMemory() {
    for (int i = 0; i < 100; i++) {
        cout << a[i] << " "; 
    }
    cout << endl;
}

int printFlag(int flag) {
    int val = 2;
    return sc_regGet(flag, &val);
}

int sc_memoryInit () {
    for (int i = 0; i < 100; i++) {
        a[i] = 0;
    }
    return 0;
}

int sc_memorySet(int address, int value) {
    if (address < 0 || address > 100){
        cout << "ошибка выхода за границы памяти" << endl;
        return -1;
    }
    a[address] = value;
    return 0;
} 

int sc_memoryGet (int address, int *value) {
    if (address < 0 || address > 100){
        cout << "ошибка выхода за границы памяти" << endl;
        return -1;
    }
    return  *value = a[address];
} 

int sc_memorySave(char *filename) {
    FILE *in = fopen(filename, "w+b");
     if (in == NULL) {
        return -1;
    }
    for (int i = 0; i < 100; i++) {
        fwrite(&a[i], sizeof(int), 1, in);
    }
    fclose(in);
    return 0;
}

int sc_memoryLoad (char *filename)  {
    FILE *out = fopen(filename, "rb");
    if (out == NULL) {
        return -1;
    }
    for (int i = 0; i < 100; i++) {
         fread(a, sizeof(a), 1, out);
    }
    fclose(out);
    return 0;
}

int sc_regInit (void) {
    flag = 0;
    return 0;
}

int sc_regSet (int reg, int value) {
    if (value < 0 || value > 5) {
        cout << "ошибка выхода за границы знчения регистра" << endl;
        return -1;
    }
    if (reg < 0 || reg > 5) {
         cout << "ошибка выхода за границы возможных флагов" << endl;
        return -1;
    }
    
    if (value == 1) {
        flag = flag | (1 << (reg - 1));
    } else {
        flag = flag & (~(1 << (reg - 1)));
    }
}

int sc_regGet (int reg, int *value) {
    if (reg < 0 || reg > 5) {
         cout << "ошибка выхода за границы возможных флагов" << endl;
        return -1;
    }
    return *value = (flag >> (reg - 1)) & 0x1;
}

int sc_commandEncode(int command, int operand, int *value) {
    for (int i = 0; i < 37; i++) {
        if (commands[i] == command) {
            return *value = (command & 0x7F) << 7 | (operand & 0x7F);
        }
    } 
	return -1;
}

int sc_commandDecode (int value, int *command,int *operand) {
    if (!value || value >> 14 || !command || !operand) {
		return -1;
	}

	*operand = value & 0x7F;
	*command = (value >> 7) & 0x7F;

    return 0;
}