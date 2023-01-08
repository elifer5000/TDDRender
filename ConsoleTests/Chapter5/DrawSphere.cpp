#include "DrawSphere.h"
#include "Canvas.h"
#include "Raycaster.h"
#include "Primitives/Sphere.h"

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
    int canvasPx = 200;
    Canvas canvas(canvasPx, canvasPx);

    // Ray starting point
    auto rayOrigin = Tuple::CreatePoint(0, 0, -5);

    // Wall parameters
    double wallZ = 10;  // Distance along the linesight
    double wallSize = 7;
    double half = wallSize / 2;

    double pixelSize = wallSize / canvasPx; // Units per pixel
    
    auto red = Color(1, 0, 0);
    auto sphere = Sphere();

    sphere.setTransform(Transforms::MakeShear(1, 0, 0, 0, 0, 0) * Transforms::MakeScale(0.5, 1, 1));

    for (int y = 0; y < canvasPx; y++) {
        for (int x = 0; x < canvasPx; x++) {
            auto direction = Tuple::CreatePoint(x * pixelSize - half, half - y * pixelSize, wallZ) - rayOrigin;
            auto ray = Ray(rayOrigin, direction.normalize());
            auto intersections = ray.intersect(sphere);
            auto hit = intersections.hit();
            if (hit && hit->m_object == &sphere) {
                canvas.writePixel(x, y, red);
            }
        }
    }

    canvas.saveToPPM("sphere_notshaded");
}

void DrawSphere() {
    //DrawSphereMyMethod();
    DrawSphereBookMethod();
}