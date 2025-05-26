#ifndef GATE_H
#define GATE_H

#include "qubit.hpp"

class Gate {
public:
    ////////// КОНСТРУКТОРЫ И ДЕСТРУКТОР //////////

    Gate(const int length, const Complex* items) {
        size = length;
        data = new Complex[length * length];
        for (int index = 0; index < (length * length); index++) {
            data[index] = items[index];
        }
    }

    ~Gate() {
        delete[] data;
    }

    //////////  ОСНОВНЫЕ ФУНКЦИИ //////////

    int GetSize() const {
        return size;
    }

    Complex operator[](int index) const {
        if (index >= (size * size) || index < 0) {
            throw std::out_of_range("Wrong index");
        }
        return data[index];
    }

    Complex operator()(int i, int j) const {
        if (i < 0 || i >= size || j < 0 || j >= size) {
            throw std::out_of_range("Wrong index");
        }
        return data[i * size + j];
    }

    Qubit operator*(const Qubit& q) const {
        Complex* list_tmp = new Complex[q.GetSize()];
        for (int i = 0; i < q.GetSize(); i++) {
            Complex tmp = Complex(0.0, 0.0);
            for (int j = 0; j < q.GetSize(); j++) {
                tmp = tmp + data[i * size + j] * q[j];
            }
            list_tmp[i] = tmp;
        }
        return {q.GetSize(), list_tmp};
    }

    Gate operator*(const Gate& g) const {
        Complex* list_tmp = new Complex[g.GetSize() * g.GetSize()];
        for (int i = 0; i < g.GetSize(); i++) {
            for (int j = 0; j < g.GetSize(); j++) {
                Complex tmp = Complex(0.0, 0.0);
                for (int k = 0; k < g.GetSize(); k++) {
                    tmp = tmp + data[i * size + k] * g[k * size + j];
                }
                list_tmp[i * g.GetSize() + j] = tmp;
            }
        }
        return {g.GetSize(), list_tmp};
    }

private:
    int size;
    Complex* data;
};

inline void print(const Gate& gate) {
    std::cout << "{";
    for (int i = 0; i < gate.GetSize(); i++) {
        std::cout << "(";
        for (int j = 0; j < gate.GetSize(); j++) {
            print(gate(i, j));
            if (j != gate.GetSize() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << ")";
        if (i != gate.GetSize() - 1) {
            std::cout << ",\n\t\t";
        }
    }
    std::cout << "}" << std::endl;
}

#endif
