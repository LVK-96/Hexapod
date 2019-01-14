#ifndef VEC_H_
#define VEC_H_

struct vec3 {
    vec3() {}
    vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    
    float x = 0, y = 0, z = 0;

    vec3& operator+=(const vec3& a)
    {
        x += a.x;
        y += a.y;
        z += a.z;
        return *this;
    }

    friend vec3 operator+(vec3 a, const vec3& b)
    {
        a += b;
        return a;
    }

    vec3& operator-=(const vec3& a)
    {
        x -= a.x;
        y -= a.y;
        z -= a.z;
        return *this;
    }

    friend vec3 operator-(vec3 a, const vec3& b)
    {
        a -= b;
        return a;
    }

    vec3& operator*=(const float& a)
    {
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }

    friend vec3 operator*(vec3 a, const float& b)
    {
        a *= b;
        return a;
    }
};

#endif
