#pragma once

#include <math.h>

class Vector3 {
    public:
        Vector3() {};
        Vector3(float _x, float _y, float _z);
        double length();
        double distanceTo(Vector3 v);
        double distBetween(Vector3 v1, Vector3 v2);

        float x = 0.f;
        float y = 0.f;
        float z = 0.f;

        Vector3 operator + (const Vector3 &in) {
            Vector3 res(x+in.x, y+in.y, z+in.z);
            return res;
        }

        Vector3 operator - (const Vector3 &in) {
            Vector3 res(x-in.x, y-in.y, z-in.z);
            return res;
        }

        Vector3 operator * (float a) {
            Vector3 res(x*a,y*a,z*a);
            return res;
        }

        Vector3 operator / (float a) {
            Vector3 res(x/a, y/a, z/a);
            return res;
        }
};

Vector3::Vector3(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

double Vector3::length()
{
    return std::sqrt(x*x + y*y + z*z);
}

double Vector3::distanceTo(Vector3 v)
{
    return std::sqrt( pow(x-v.x,2) + pow(y-v.y,2) + pow(z-v.z,2) );
}

double Vector3::distBetween(Vector3 v1, Vector3 v2)
{
    return std::sqrt( pow(v1.x-v2.x,2) + pow(v1.y-v2.y,2) + pow(v1.z-v2.z,2) );
}