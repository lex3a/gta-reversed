/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class  CVector2D
{
public:
    float x, y;
    
    inline CVector2D() {
        x = 0.0f;
        y = 0.0f;
    }

    inline CVector2D(float X, float Y) {
        x = X;
        y = Y;
    }

    CVector2D(const class CVector& vec3d);

    static void InjectHooks();

	// Returns length of vector
	float Magnitude();
    void Normalise();
    inline float SquaredMagnitude()
    {
        return x * x + y * y ;
    }

	void operator=(const CVector2D& right);

    inline CVector2D(CVector2D const& src) {
        x = src.x; y = src.y;
    }

    inline void Sum(CVector2D &a, CVector2D &b) {
        this->x = a.x + b.x;
        this->y = a.y + b.y;
    }

    inline void Difference(CVector2D &a, CVector2D &b) {
        this->x = a.x - b.x;
        this->y = a.y - b.y;
    }

    inline void operator+=(const CVector2D& right) {
        this->x += right.x;
        this->y += right.y;
    }

    inline void operator-=(const CVector2D& right) {
        this->x -= right.x;
        this->y -= right.y;
    }

    inline void operator *= (float multiplier) {
        this->x *= multiplier;
        this->y *= multiplier;
    }

    inline void operator /= (float divisor) {
        this->x /= divisor;
        this->y /= divisor;
    }

    inline void Set(float X, float Y) {
        x = X; y = Y;
    }
};

inline CVector2D operator-(const CVector2D& vecOne, const CVector2D& vecTwo) {
    return CVector2D(vecOne.x - vecTwo.x, vecOne.y - vecTwo.y);
}

inline float DistanceBetweenPoints2D(const CVector2D &pointOne, const CVector2D &pointTwo) {
    return (pointTwo - pointOne).Magnitude();
}

inline float DistanceBetweenPointsSquared2D(const CVector2D& pointOne, const CVector2D& pointTwo) {
    return (pointTwo - pointOne).SquaredMagnitude();
}

inline float DotProduct2D(const CVector2D& v1, const CVector2D& v2)
{
    return v1.y * v2.y + v1.x * v2.x;
}
