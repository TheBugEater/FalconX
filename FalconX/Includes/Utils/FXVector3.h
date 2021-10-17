#pragma once

class FXVector3
{
public:
    FXVector3();
    FXVector3(float x, float y, float z);

    FXVector3       operator+(FXVector3 vector);
    FXVector3&      operator+=(FXVector3 vector);
    FXVector3       operator-(FXVector3 vector);
    FXVector3&      operator-=(FXVector3 vector);
    FXVector3       operator*(FXVector3 vector);
    FXVector3&      operator*=(FXVector3 vector);
    FXVector3       operator/(FXVector3 vector);
    FXVector3&      operator/=(FXVector3 vector);
    bool            operator==(FXVector3 vector);

    FXVector3&      operator=(FXVector3 vector);

    FXVector3       operator*(float value);
    FXVector3&      operator*=(float value);
    FXVector3       operator/(float value);
    FXVector3&      operator/=(float value);

    FXVector3&      Normalize();
    float           Magnitude();

    float           X;
    float           Y;
    float           Z;
};