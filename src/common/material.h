#ifndef MATERIA_H
#define MATERIAL_H
#include "rtweekend.h"
#include "hittableObject.h"

class Material
{
    public:
        virtual bool Scatter(const Ray& ray_in, const HitRecord& record, color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material
{
    public:
        Lambertian(const color& albedo) : m_albedo(albedo){}
        virtual bool Scatter(const Ray& ray_in, const HitRecord& record, color& attenuation, Ray& scattered) const override
        {
            auto scatterDir = record.normal + random_unit_vector();

            // Catch degenerate scatter direction
            if(scatterDir.near_zero())
            {
                scatterDir = record.normal;
            }

            scattered = Ray(record.p, scatterDir);
            attenuation = m_albedo;
            return true;
        }

    private:
        color m_albedo;
};

class Metal : public Material
{
    public:
        Metal(const color& albedo) : m_albedo(albedo){}
        virtual bool Scatter(const Ray& ray_in, const HitRecord& record, color& attenuation, Ray& scattered) const override
        {
            vec3 reflected = reflect(unit_vector(ray_in.GetDirection()), record.normal);
            scattered = Ray(record.p, reflected);
            attenuation = m_albedo;
            return (dot(scattered.GetDirection(), record.normal) > 0);
        }

    private:
        color m_albedo;
};


#endif
