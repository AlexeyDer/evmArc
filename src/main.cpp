#include "mySimpleComputer.h"

int main() {
    sc_memoryInit();

    cout << "Замена ячейки памяти по ядресу: " << endl;
    sc_memorySet(2, 2);
    sc_memorySet(3, 3);
    sc_memorySet(200, 2);

    cout << "Получение элемента по адресу: " << endl;
    int value = -1;
    value = sc_memoryGet(3, &value);
    cout << value << endl;
      value = sc_memoryGet(1, &value);
    cout << value << endl;
      value = sc_memoryGet(250, &value);
    cout << value << endl;
  
    sc_memorySave((char*)"binfile.bin");
    sc_memoryLoad((char*)"binfile.bin");

    sc_regInit();
    cout << "Инициализация флагов: "<< flag << endl;
    
    // sc_regSet(A, 1); 
	// sc_regSet(B, 1);
	// sc_regSet(C, 1);
	// sc_regSet(D, 1);
	// sc_regSet(E, 1);

    cout << "Инициализация флагов: "<< flag << endl;

    
    cout << "Флаг A: " << printFlag(A) << endl;

    int flag_D = sc_regGet(D, &flag_D);
    cout << "Флаг D: " << flag_D << endl;

    int flag_E = sc_regGet(E, &flag_E);
    cout << "Флаг E: " << flag_E << endl;

    cout << "Memory: ";
    printMemory();

    int cmd_encode = sc_commandEncode(0x10, 4, &cmd_encode); 
		cout << "Команда закодирована: " << cmd_encode << endl;
	
	int op_decode, cmd_decode;
		sc_commandDecode(cmd_encode, &cmd_decode, &op_decode); 
		cout << "Команда разкодирована: " << cmd_decode << endl;
        cout << "Разкодированный операнд: " << op_decode << endl; 

    cout << endl << endl;
    return 0;
}