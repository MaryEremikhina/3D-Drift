#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "gate.hpp"

////////// ПЕРВОЕ ЗАДАНИЕ //////////

inline const Qubit b0 = Qubit(Complex(1.0, 0.0), Complex(0.0, 0.0));
inline const Qubit b1 = Qubit(Complex(0.0, 0.0), Complex(1.0, 0.0));

inline const Gate gX = Gate(2, new Complex[4]{Complex(0.0, 0.0), Complex(1.0, 0.0),
                                                    Complex(1.0, 0.0), Complex(0.0, 0.0)});
inline const Gate gY = Gate(2, new Complex[4]{Complex(0.0, 0.0), Complex(0.0, -1.0),
                                                    Complex(1.0, 0.0), Complex(0.0, 0.0)});
inline const Gate gZ = Gate(2, new Complex[4]{Complex(1.0, 0.0), Complex(0.0, 0.0),
                                                    Complex(0.0, 0.0), Complex(-1.0, 0.0)});
inline const Gate gH = Gate(2, new Complex[4]{Complex(1.0, 0.0) * (1 / sqrt(2)),
                                                    Complex(1.0, 0.0) * (1 / sqrt(2)),
                                                    Complex(1.0, 0.0) * (1 / sqrt(2)),
                                                    Complex(-1.0, 0.0) * (1 / sqrt(2))});
inline const Gate CNOT = Gate(4, new Complex[16] {
    Complex(1.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0),
    Complex(0.0, 0.0), Complex(1.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0),
    Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(1.0, 0.0),
    Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(1.0, 0.0), Complex(0.0, 0.0),
});

////////// ВТОРОЕ ЗАДАНИЕ //////////

inline const Gate CNOT1 = Gate(8, new Complex[64] {
    Complex(1.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0),
    Complex(0.0, 0.0), Complex(1.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0),
    Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(1.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0),
    Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(1.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0),
    Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(1.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0),
    Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(1.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0),
    Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(1.0, 0.0),
    Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(1.0, 0.0), Complex(0.0, 0.0)
});

inline const Gate CNOT2 = Gate(8, new Complex[64] {
    Complex(1.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0),
    Complex(0.0, 0.0), Complex(1.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0),
    Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(1.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0),
    Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(1.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0),
    Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(1.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0),
    Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(1.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0),
    Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(1.0, 0.0),
    Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(1.0, 0.0), Complex(0.0, 0.0)
});

inline Qubit Oraclef1(const Qubit& q1, const Qubit& q2) {
    return q1 * (gX * q2);
}

inline Qubit OracleXOR(const Qubit& q1, const Qubit& q2, const Qubit& y) {
    Qubit state = q1 * q2 * y;
    return (CNOT1 * CNOT2) * state;
}

////////// ТРЕТЬЕ ЗАДАНИЕ //////////

inline Qubit GroverAlgo(bool func(bool, bool)) {
    Qubit tmp = Qubit(Complex(1.0, 0.0), Complex(1.0, 0.0), Complex(1.0, 0.0), Complex(1.0, 0.0));
    Complex *list_tmp = new Complex[16];
    list_tmp[0] = Complex(func(false, false) ? -1.0 : 1.0, 0.0);
    list_tmp[5] = Complex(func(false, true) ? -1.0 : 1.0, 0.0);
    list_tmp[10] = Complex(func(true, false) ? -1.0 : 1.0, 0.0);
    list_tmp[15] = Complex(func(true, true) ? -1.0 : 1.0, 0.0);

    Gate CCNOT = Gate(4, list_tmp);
    Complex *list_D = new Complex[16];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            list_D[i * 4 + j] = Complex(i == j ? -0.5 : 0.5, 0.0);
    }
    Gate D(4, list_D);
    return D * (CCNOT * tmp);
}


#endif
