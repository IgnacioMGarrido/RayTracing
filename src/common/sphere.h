#ifndef SPHERE_H
#define SPHERE_H

#include "hittableObject.h"

class Sphere : public HittableObject
{
    public:
        Sphere() = default;
        Sphere(point3 centre, double r, std::shared_ptr<Material> material)
        : m_centre(centre)
        , m_radius(r)
        , m_material(material)
        {};

        virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override
        {
            vec3 oc = r.GetOrigin() - m_centre;
            auto a = r.GetDirection().length_squared();
            auto halfB = dot(oc, r.GetDirection());
            auto c = oc.length_squared() - m_radius * m_radius;
            auto disc = halfB * halfB - a * c;

            if(disc < 0)
            {
                return false;
            }
            
            auto discSqrt = sqrt(disc);

            auto root = (-halfB - discSqrt) / a;
            if(root < t_min || root > t_max)
            {
                root = (-halfB - discSqrt) / a;
                if (root < t_min || root > t_max)
                    return false;
            }

            rec.t = root;
            rec.p = r.At(rec.t);
            //rec.normal = (rec.p - m_centre) / m_radius;
            vec3 outwardNormal = (rec.p - m_centre) / m_radius;
            rec.setFaceNormal(r, outwardNormal);
            rec.material = m_material;

            return true;
        }


    private:
        point3 m_centre;
        double m_radius;
        std::shared_ptr<Material> m_material;
};
#endif