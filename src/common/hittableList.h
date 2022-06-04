#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>
#include <memory>
#include "hittableObject.h"

class HittableList : public HittableObject
{
    public:
        HittableList() = default;
        HittableList(std::shared_ptr<HittableObject> object) { Add(object); }

        void Clear() {m_objects.clear();}
        void Add(std::shared_ptr<HittableObject> object) { m_objects.push_back(object); }

        virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override
        {
            HitRecord tempRec = {};
            bool hitAnything = false;
            auto closestSoFar = t_max;

            for(const auto& object : m_objects)
            {
                if(object->Hit(r, t_min, closestSoFar, tempRec))
                {
                    hitAnything = true;
                    closestSoFar = tempRec.t;
                    rec = tempRec;
                }
            }

            return hitAnything;
        }

    public:
        std::vector<std::shared_ptr<HittableObject>> m_objects;
};

#endif