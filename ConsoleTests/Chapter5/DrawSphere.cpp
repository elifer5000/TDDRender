#include "DrawSphere.h"
#include "Canvas.h"
#include "Raycaster.h"
#include "Primitives/Sphere.h"

void DrawSphere() {
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