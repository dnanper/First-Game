// #pragma once

// #include "Vector2_PI.hpp"
// #include <math.h>
// #include <stdint.h>

// template <class Num_T>
// class Vector2 
// {
// public:
//     Vector2();
//     Vector2(Num_T x, Num_T y);
//     ~Vector2(){}

// public:
//     Vector2 operator+(const Vector2 &rhs) const;
//     Vector2 operator-(const Vector2 &rhs) const;
//     Vector2 operator*(Num_T value) const;
//     Vector2 operator/(Num_T value) const;

//     Vector2 &operator+=(const Vector2 &rhs);
//     Vector2 &operator-=(const Vector2 &rhs);
//     Vector2 &operator*=(Num_T value);
//     Vector2 &operator/=(Num_T value);

//     bool operator==(const Vector2 &rhs) const;
//     bool operator!=(const Vector2 &rhs) const;

// public:
//     Vector2 Rotate(double angle) const;
//     void RotateIp(double angle);

//     double AngleTo(const Vector2 &other) const;
//     double AngleTo(Num_T x, Num_T y) const;

//     Vector2<double> Normalize() const;
//     void NormalizeIp();

//     double Dot(const Vector2 &other) const;
//     double Dot(Num_T x, Num_T y) const;

//     double DistanceTo(const Vector2 &other) const;

//     double Length() const;
//     double LengthSquared() const;

// public:
//     Num_T x;
//     Num_T y;
// };

// template <class Num_T>
// Vector2<Num_T>::Vector2() 
// {
//     x = (Num_T)0;
//     y = (Num_T)0;
// }

// template <class Num_T>
// Vector2<Num_T>::Vector2(Num_T x, Num_T y) 
// {
//     this->x = x;
//     this->y = y;
// }

// template <class Num_T>
// Vector2<Num_T> Vector2<Num_T>::operator+(const Vector2 &rhs) const 
// {
//     return {x + rhs.x, y + rhs.y};
// }

// template <class Num_T>
// Vector2<Num_T> Vector2<Num_T>::operator-(const Vector2 &rhs) const 
// {
//     return {x - rhs.x, y - rhs.y};
// }

// template <class Num_T>
// Vector2<Num_T> Vector2<Num_T>::operator*(Num_T value) const 
// {
//     return {x * value, y * value};
// }

// template<class Num_T>
// Vector2<Num_T> Vector2<Num_T>::operator/(Num_T value) const
// {
//     return {x / value, y / value};
// }

// template <class Num_T>
// Vector2<Num_T> &Vector2<Num_T>::operator+=(const Vector2 &rhs) 
// {
//     return *this = *this + rhs;
// }

// template <class Num_T>
// Vector2<Num_T> &Vector2<Num_T>::operator-=(const Vector2 &rhs) 
// {
//     return *this = *this - rhs;
// }

// template <class Num_T>
// Vector2<Num_T> &Vector2<Num_T>::operator*=(Num_T value) 
// {
//     return *this = *this * value;
// }

// template <class Num_T>
// bool Vector2<Num_T>::operator==(const Vector2<Num_T> &rhs) const 
// {
//     return x == rhs.x && y == rhs.y;
// }

// template <class Num_T>
// bool Vector2<Num_T>::operator!=(const Vector2<Num_T> &rhs) const 
// {
//     return !(*this == rhs);
// }

// template <class Num_T>

// Vector2<Num_T> Vector2<Num_T>::Rotate(double angle) const 
// {
//     angle = fmod(angle, 360.f);
//     angle = DEG2RAD(angle);
//     double sinAngle = sin(angle);
//     double cosAngle = cos(angle);

//     double tmpX = (cosAngle * x - sinAngle * y);
//     double tmpY = (sinAngle * x + cosAngle * y);
//     return Vector2<Num_T>(tmpX, tmpY);
// }

// template <class Num_T>
// void Vector2<Num_T>::RotateIp(double angle) 
// {
//     Vector2<double> newV = Rotate(angle);
//     x = newV.x;
//     y = newV.y;
// }

// template <class Num_T>
// double Vector2<Num_T>::AngleTo(const Vector2 &other) const 
// {
//     return AngleTo(other.x, other.y);
// }

// template <class Num_T>
// double Vector2<Num_T>::AngleTo(Num_T x, Num_T y) const 
// {
//     return RAD2DEG(atan2(y, x) - atan2(this->y, this->x));
// }

// template <class Num_T>
// Vector2<double> Vector2<Num_T>::Normalize() const 
// {
//     double s = Length();
//     if (s == 0.f) {
//         return {0.f, 0.f};
//     }
//     return {x / s, y / s};
// }

// template <class Num_T>
// void Vector2<Num_T>::NormalizeIp() 
// {
//     Vector2<double> newV = Normalize();
//     x = newV.x;
//     y = newV.y;
// }

// template <class Num_T>
// double Vector2<Num_T>::Dot(const Vector2 &other) const 
// {
//     return Dot(other.x, other.y);
// }



// template <class Num_T>
// double Vector2<Num_T>::Dot(Num_T x, Num_T y) const 
// {
//     return (this->x * x) + (this->y * y);
// }

// template <class Num_T>
// double Vector2<Num_T>::DistanceTo(const Vector2 &other) const 
// {
//     return DistanceTo(other.x, other.y);
// }

// template <class Num_T>
// double Vector2<Num_T>::Length() const {
//     return sqrtf(LengthSquared());
// }
// template <class Num_T>
// double Vector2<Num_T>::LengthSquared() const {
//     return x * x + y * y;
// }

// typedef Vector2<int32_t> Vector2i;
// typedef Vector2<uint32_t> Vector2u;
// typedef Vector2<double> Vector2f;

#include <iostream>
#include "Vector2_PI.hpp"

struct Vector2
{ 
public:
    double x_;
    double y_;
    Vector2();
    Vector2(double x, double y);
    ~Vector2();

    double GetX() const;
    double GetY() const;

    void SetX(const double x);
    void SetY(const double y);

    Vector2 operator+(const Vector2 &rhs) const;
    Vector2 operator-(const Vector2 &rhs) const;
    Vector2 operator*(double value) const;
    Vector2 operator/(double value) const;

    Vector2 &operator+=(const Vector2 &rhs);
    Vector2 &operator-=(const Vector2 &rhs);
    Vector2 &operator*=(double value);

    bool operator==(const Vector2 &rhs) const;
    bool operator!=(const Vector2 &rhs) const;

    Vector2 Rotate(double angle) const;
    void RotateIp(double angle);

    double AngleTo(const Vector2 &other) const;
    double AngleTo(double x, double y) const;

    Vector2 Normalize() const;
    void NormalizeIp();

    double Dot(const Vector2 &other) const;
    double Dot(double x, double y) const;

    // double DistanceTo(const Vector2 &other) const;

    double LengthSquared() const;
    double Length() const;

};
