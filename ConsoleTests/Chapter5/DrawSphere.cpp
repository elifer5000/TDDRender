#include <chrono>
#include <omp.h>
#include "DrawSphere.h"
#include "Canvas.h"
#include "Raycaster.h"
#include "Primitives/Sphere.h"
#include "Light.h"

void DrawSphereMyMethod() {
    int w = 400, h = 400;
    Canvas canvas(w, h);

    auto red = Color(1, 0, 0);
    auto black = Color(0, 0, 0);

    auto sphere = Sphere();
    double radius = 180;
    auto transform = Transforms::MakeTranslation(w / 2, radius + 10, h / 2) * Transforms::MakeScale(radius, radius, radius);
    sphere.setTransform(transform);

    // Draw row by row, pixel by pixel
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            auto ray = Ray(Tuple::CreatePoint(i, 0, j), Tuple::CreateVector(0, 1, 0));
            auto intersections = ray.intersect(sphere);
            auto hit = intersections.hit();
            if (hit && hit->m_object == &sphere) {
                canvas.writePixel(i, j, red);
            }
            else {
                canvas.writePixel(i, j, black);
            }
        }
    }

    canvas.saveToPPM("sphere_notshaded");
}

// Book method
// Lantern --> sphere --> wall
// We are projecting the sphere's shadow onto the wall
void DrawSphereBookMethod() {
    int canvasPx = 400;
    Canvas canvas(canvasPx, canvasPx);

    // Ray starting point
    auto rayOrigin = Tuple::CreatePoint(0, 0, -5);

    // Wall parameters
    double wallZ = 10;  // Distance along the linesight
    double wallSize = 7;
    double half = wallSize / 2;

    double pixelSize = wallSize / canvasPx; // Units per pixel
    
    // Light
    auto light = PointLight(Tuple::CreatePoint(-10, 10, -10), Color(1, 1, 1));

    // Sphere
    auto red = Color(1, 0, 0);
    auto sphere = Sphere();
    Material material = sphere.getMaterial();
    material.m_color = Color(1, 0.2, 1);
    sphere.setMaterial(material);

    sphere.setTransform(Transforms::MakeShear(1, 0, 0, 0, 0, 0) * Transforms::MakeScale(0.5, 1, 1));

    #pragma omp parallel for num_threads(4) collapse(2)
    for (int y = 0; y < canvasPx; y++) {
        for (int x = 0; x < canvasPx; x++) {
            auto direction = Tuple::CreatePoint(x * pixelSize - half, half - y * pixelSize, wallZ) - rayOrigin;
            auto ray = Ray(rayOrigin, direction.normalize());
            auto intersections = ray.intersect(sphere);
            auto hit = intersections.hit();
            if (hit && hit->m_object == &sphere) {
                auto hitPoint = ray.position(hit->m_t);
                auto normal = sphere.normalAt(hitPoint);
                auto eye = -ray.m_direction;
                auto c = lighting(sphere.getMaterial(), light, hitPoint, eye, normal);
                canvas.writePixel(x, y, c);
            }
        }
    }

    canvas.saveToPPM("sphere_shaded");
}

void DrawSphere() {
    auto start = std::chrono::steady_clock::now();
    //DrawSphereMyMethod();
    DrawSphereBookMethod();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}