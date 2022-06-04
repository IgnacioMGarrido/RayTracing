#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
class Material;

struct HitRecord
{
    point3 p;
    vec3 normal;
    double t;
    bool frontFace;
    std::shared_ptr<Material> material;
    inline void setFaceNormal(const Ray& ray, const vec3& outwardNormal)
    {
        frontFace = dot(ray.GetDirection(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class HittableObject
{
public:
    virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};

#endif