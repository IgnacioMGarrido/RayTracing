#include "rtweekend.h"
#include "camera.h"
#include "color.h"
#include "hittableList.h"
#include "sphere.h"

#include <iostream>

color ray_color(const Ray& ray, const HittableObject& world, int depth)
{
    HitRecord record{};
    if(depth <= 0)
    {
        return color(0,0,0);
    }

    if(world.Hit(ray, 0.001, infinity, record))
    {
        point3 target = record.p + record.normal + random_in_unit_sphere();
        return 0.5 * ray_color(Ray(record.p, target - record.p), world, depth - 1);
    }

    vec3 unitDir = unit_vector(ray.GetDirection());
    auto t = 0.5 * (unitDir.y() + 1.0);

    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World
    HittableList world;
    world.Add(std::make_shared<Sphere>(point3(0,0,-1), 0.5));
    world.Add(std::make_shared<Sphere>(point3(0,-100.5,-1), 100));

    // Camera

    Camera cam;
    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixelColor(0,0,0);
            for(int s = 0; s < samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);

                Ray r = cam.get_ray(u,v);
                pixelColor += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixelColor, samples_per_pixel);
        }
    }
    
    std::cerr << "\nDone.\n";
}