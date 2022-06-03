#ifndef RAY_H
#define RAY_H
#include "vec3.h"

class Ray
{
public:
    Ray(){}
    Ray(const point3& origin, const vec3& dir)
        :m_origin(origin)
        , m_dir(dir)
    {
    }

    point3 GetOrigin() const { return m_origin; }
    vec3 GetDirection() const { return m_dir; }

    point3 At(double t){ return m_origin + t * m_dir; }
private:
    point3 m_origin;
    vec3 m_dir;
};

#endif