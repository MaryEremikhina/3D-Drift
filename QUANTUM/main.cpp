#include "constants.h"
// 38 + 25 + 28 + (40)

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
bool f(bool a, bool b) {
    return (a and b);
}

int main() {
    ////////// ПЕРВОЕ ЗАДАНИЕ //////////

    std::cout << "---------------FIRST TASK---------------\n\n";

    std::cout << "Qubit |0>: ";
    print(b0);
    std::cout << "Qubit |1>: ";
    print(b1);
    std::cout << "Qubit |101>: ";
    print(b1 * b0 * b1);

    std::cout << "Tensor product |0> * |1>: ";
    print(b0 * b1);

    std::cout << "Pauli Gates: \n";
    std::cout << "XGate: ";
    print(gX);
    std::cout << "YGate: ";
    print(gY);
    std::cout << "ZGate: ";
    print(gZ);

    std::cout << "HGate: ";
    print(gH);
    std::cout << "CNOT: ";
    print(CNOT);

    std::cout << "XGate |0>: ";
    print(gX * b0);
    std::cout << "HGate |0>: ";
    print(gH * b0);
    std::cout << "CNOT |10>: ";
    print(CNOT * (b1 * b0));
    std::cout << std::endl;

    ////////// ВТОРОЕ ЗАДАНИЕ //////////

    std::cout << "---------------SECOND TASK---------------\n\n";
    std::cout << "Oraclef1 |x>|y>: |x> * (gX * |y>)\n";
    std::cout << "OracleXOR |x1, x2>|y>: (CNOT1 * CNOT2) * (|x1> * |x2> * |y>)\n";

    std::cout << "Oraclef1 |00>: ";
    print(Oraclef1(b0, b0));
    std::cout << "OracleXOR |010>: ";
    print(OracleXOR(b0, b1, b0));
    std::cout << std::endl;

    ////////// ТРЕТЬЕ ЗАДАНИЕ //////////

    std::cout << "---------------THIRD TASK---------------\n\n";
    std::cout << "Algorithm Grover X ^ Y: Diffuser * (CCNOT * (1 1 1 1))\n";
    std::cout << "Algorithm Grover X ^ Y: ";
    print(GroverAlgo(f));
    return 0;
}