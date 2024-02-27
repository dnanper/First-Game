#include "Vector2.hpp"
#include "Vector2_PI.hpp"
#include <math.h>
#include <iostream>

Vector2::Vector2() : x_(0), y_(0)
{ }

Vector2::Vector2(double x, double y)
    : x_(x), y_(y)
{ }

Vector2::~Vector2()
{ }

double Vector2::GetX() const
{
    return x_;
}

double Vector2::GetY() const
{
    return y_;
}

void Vector2::SetX(const double x)
{
    x_ = x;
}

void Vector2::SetY(const double y)
{
    y_ = y;
}

Vector2 Vector2::operator+(const Vector2 &rhs) const 
{
    return {x_ + rhs.x_, y_ + rhs.y_};
}

Vector2 Vector2::operator-(const Vector2 &rhs) const 
{
    return {x_ - rhs.x_, y_ - rhs.y_};
}

Vector2 Vector2::operator*(double value) const
{
    return { x_ * value, y_ * value};
}

Vector2 Vector2::operator/(double value) const
{
    return { x_ / value, y_ / value};
}

Vector2& Vector2::operator+=(const Vector2 &rhs) 
{
    return *this = *this + rhs;
}

Vector2& Vector2::operator-=(const Vector2 &rhs) 
{
    return *this = *this - rhs;
}

Vector2& Vector2::operator*=(double value) 
{
    return *this = *this * value;
}

bool Vector2::operator==(const Vector2 &rhs) const 
{
    return x_ == rhs.x_ && y_ == rhs.y_;
}

bool Vector2::operator!=(const Vector2 &rhs) const 
{
    return !(*this == rhs);
}

Vector2 Vector2::Rotate(double angle) const 
{
    angle = fmod(angle, 360.f);
    angle = DEG2RAD(angle);
    double sinAngle = sin(angle);
    double cosAngle = cos(angle);

    double tmpX = (cosAngle * x_ - sinAngle * y_);
    double tmpY = (sinAngle * x_ + cosAngle * y_);
    return Vector2(tmpX, tmpY);
}

void Vector2::RotateIp(double angle) 
{
    Vector2 newV = Rotate(angle);
    x_ = newV.x_;
    y_ = newV.y_;
}

double Vector2::AngleTo(const Vector2 &other) const 
{
    return AngleTo(other.x_, other.y_);
}

double Vector2::AngleTo(double x, double y) const 
{
    return RAD2DEG(atan2(y, x) - atan2(this->y_, this->x_));
}

Vector2 Vector2::Normalize() const
{
    double s = Length();
    if (s == 0.f) {
        return {0.f, 0.f};
    }
    return {x_ / s, y_ / s};
}

void Vector2::NormalizeIp()
{
    Vector2 newV = Normalize();
    x_ = newV.x_;
    y_ = newV.y_;
}

double Vector2::Dot(const Vector2 &other) const
{
    return Dot(other.x_, other.y_);
}

double Vector2::Dot(double x, double y) const
{
    return (this->x_ * x) + (this->y_ * y);
}

// double Vector2::DistanceTo(const Vector2 &other) const
// {
//     return DistanceTo(other.x_, other.y_);
// }

double  Vector2::LengthSquared() const
{
    return x_ * x_ + y_ * y_;
}

double Vector2::Length() const
{
    return sqrtf(LengthSquared());
}
