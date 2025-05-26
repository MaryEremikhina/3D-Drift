#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>

class Complex {
public:
    ////////// КОНСТРУКТОРЫ И ДЕСТРУКТОР //////////

    Complex() {
        real = 0.0;
        img = 0.0;
    }
    Complex(const double a, const double b) {
        real = a;
        img = b;
    }

    ~Complex()= default;

    ////////// ГЕТЕРЫ И СЕТЕРЫ //////////

    void SetReal(const double a) {
        real = a;
    }

    void SetImg(const double b) {
        img = b;
    }

    double GetReal() const {
        return real;
    }

    double GetImg() const {
        return img;
    }

    ////////// ОСНОВНЫЕ ФУНКЦИИ //////////

    double Module() const {
        return sqrt(real * real + img * img);
    }

    Complex operator+(const Complex& other) const {
        return {real + other.GetReal(), img + other.GetImg()};
    }

    Complex operator-(const Complex& other) const {
        return {real - other.GetReal(), img - other.GetImg()};
    }

    Complex operator-() const {
        return {-real, -img};
    }

    Complex operator*(const Complex& other) const {
        return {real * other.GetReal() - img * other.GetImg(),
            real * other.GetImg() + img * other.GetReal()};
    }

    Complex operator*(const double other) const {
        return {real * other, img * other};
    }

    Complex conjugate() const {
        return {real, -img};
    }

private:
    double real;
    double img;
};

inline bool operator==(const Complex& c1, const Complex& c2) {
    return ((c1.GetReal() == c2.GetReal()) && (c1.GetImg() == c2.GetImg()));
}

inline void print(const Complex& c) {
    if (c.GetImg() >= 0) {
        std::cout << c.GetReal() << " + " << c.GetImg() << "i";
    } else {
        std::cout << c.GetReal() << " - " << (-1.0) * c.GetImg() << "i";
    }
}

#endif