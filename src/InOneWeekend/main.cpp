#include "ray.h"
#include "color.h"
#include "vec3.h"
#include <iostream>

bool hit_sphere(const point3& center, double radius, const Ray& r)
{
    vec3 oc = r.GetOrigin() - center;
    auto a =  dot(r.GetDirection(), r.GetDirection());
    auto b = 2.0 * dot(oc, r.GetDirection());
    auto c = dot(oc, oc) - radius*radius;
    auto disc = b*b - 4*a*c;
    return (disc > 0);
}

color ray_color(const Ray& ray)
{
    if(hit_sphere(point3(0,0,-1), 0.5, ray))
    {
        return color(1, 0, 0);
    }
    vec3 unitDirection = unit_vector(ray.GetDirection());
    auto t = 0.5*(unitDirection.y() + 1.0);
    return (1.0-t) * color(1.0,1.0,1.0) + t*color(0.5,0.7,1.0);
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color,1);
        }
    }
}