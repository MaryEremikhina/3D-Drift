#ifndef QUBIT_H
#define QUBIT_H

#include <iostream>
#include "complex.hpp"

class Qubit {
public:
    ////////// КОНСТРУКТОРЫ И ДЕСТРУКТОР //////////

    Qubit(const Complex& c1, const Complex& c2) {
        size = 2;
        items = new Complex[2]{c1, c2};
        k = 1 / sqrt(c1.Module() * c1.Module() + c2.Module() * c2.Module());
        normalise();
    }

    Qubit(const Complex& c1, const Complex& c2, const Complex& c3, const Complex& c4) {
        size = 4;
        items = new Complex[4]{c1, c2, c3, c4};
        k = 1 / sqrt(c1.Module() * c1.Module() + c2.Module() * c2.Module() +
            c3.Module() * c3.Module() + c4.Module() * c4.Module());
        normalise();
    }

    Qubit(const int length, const Complex* data) {
        if (log2(length) != int(log2(length)) || data == nullptr || length < 2) {
            throw std::out_of_range("Wrong enter qubits");
        }
        size = length;
        items = new Complex[length];
        double tmp = 0.0;
        for (int index = 0; index < length; index++) {
            items[index] = data[index];
            tmp += data[index].Module() * data[index].Module();
        }
        k = 1 / sqrt(tmp);
        normalise();
    }

    ~Qubit() {
        delete[] items;
    }

    ////////// ГЕТЕРЫ И СЕТЕРЫ //////////

    int GetSize() const {
        return size;
    }

    double GetK() const {
        return k;
    }

    Complex operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Wrong index");
        }
        return items[index];
    }

    //////////  ОСНОВНЫЕ ФУНКЦИИ //////////

    void normalise() {
        for (int index = 0; index < size; index++) {
            items[index] = items[index] * k;
        }
        k = 1;
    }

    Qubit operator*(const Qubit& other) const {
        Complex* tmp = new Complex[size * other.GetSize()];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < other.GetSize(); j++) {
                tmp[i * other.GetSize() + j] = items[i] * other[j];
            }
        }
        return {size * other.GetSize(), tmp};
    }

    Qubit operator+(const Qubit& other) const {
        if (size != other.GetSize()) {
            throw std::out_of_range("Wrong size of qubit");
        }
        Complex* tmp = new Complex[size];
        for (int index = 0; index < size; index++) {
            tmp[index] = items[index] + other[index];
        }
        return {size, tmp};
    }

private:
    double k; // коэффициент для нормировки
    int size;
    Complex* items;
};

inline void print(const Qubit& q) {
    if (q.GetK() != 1) {
        std::cout << q.GetK() << " * ";
    }
    std::cout << '(';
    for (int i = 0; i < q.GetSize(); i++) {
        print(q[i]);
        if (i != q.GetSize() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << ')' << std::endl;
}

#endif