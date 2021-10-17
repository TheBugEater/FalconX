#include "Utils/FXVector3.h"

FXVector3::FXVector3()
    : X(0)
    , Y(0)
    , Z(0)
{
}

FXVector3::FXVector3(float x, float y, float z)
    : X(x)
    , Y(y)
    , Z(z)
{
}

FXVector3 FXVector3::operator+(FXVector3 vector)
{
    FXVector3 result;
    result.X = this->X + vector.X;
    result.Y = this->Y + vector.Y;
    result.Z = this->Z + vector.Z;
    return result;
}

FXVector3& FXVector3::operator+=(FXVector3 vector)
{
    this->X += vector.X;
    this->Y += vector.Y;
    this->Z += vector.Z;
    return *this;
}

FXVector3 FXVector3::operator-(FXVector3 vector)
{
    FXVector3 result;
    result.X = this->X - vector.X;
    result.Y = this->Y - vector.Y;
    result.Z = this->Z - vector.Z;
    return result;
}

FXVector3& FXVector3::operator-=(FXVector3 vector)
{
    this->X -= vector.X;
    this->Y -= vector.Y;
    this->Z -= vector.Z;
    return *this;
}

FXVector3& FXVector3::operator=(FXVector3 vector)
{
    this->X = vector.X;
    this->Y = vector.Y;
    this->Z = vector.Z;
    return *this;
}

FXVector3 FXVector3::operator*(FXVector3 vector)
{
    FXVector3 result;
    result.X = this->X * vector.X;
    result.Y = this->Y * vector.Y;
    result.Z = this->Z * vector.Z;
    return result;
}

FXVector3& FXVector3::operator*=(FXVector3 vector)
{
    this->X *= vector.X;
    this->Y *= vector.Y;
    this->Z *= vector.Z;
    return *this;
}

FXVector3 FXVector3::operator*(float value)
{
    FXVector3 result;
    result.X = this->X * value;
    result.Y = this->Y * value;
    result.Z = this->Z * value;
    return result;
}

FXVector3& FXVector3::operator*=(float value)
{
    this->X *= value;
    this->Y *= value;
    this->Z *= value;
    return *this;
}

FXVector3 FXVector3::operator/(FXVector3 vector)
{
    FXVector3 result;
    result.X = this->X / vector.X;
    result.Y = this->Y / vector.Y;
    result.Z = this->Z / vector.Z;
    return result;
}

FXVector3& FXVector3::operator/=(FXVector3 vector)
{
    this->X /= vector.X;
    this->Y /= vector.Y;
    this->Z /= vector.Z;
    return *this;
}

FXVector3 FXVector3::operator/(float value)
{
    FXVector3 result;
    result.X = this->X / value;
    result.Y = this->Y / value;
    result.Z = this->Z / value;
    return result;
}

FXVector3& FXVector3::operator/=(float value)
{
    this->X /= value;
    this->Y /= value;
    this->Z /= value;
    return *this;
}

bool FXVector3::operator==(FXVector3 vector)
{
    return 
        (this->X == vector.X 
        && this->Y == vector.Y 
        && this->Z == vector.Z);
}

FXVector3& FXVector3::Normalize()
{
    return *this;
}

float FXVector3::Magnitude()
{
    return 0;
}


