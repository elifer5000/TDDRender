#define _USE_MATH_DEFINES

#include <cmath>
#include "Tuple.h"
#include "Color.h"
#include "Matrix.h"
#include "Canvas.h"

void DrawClock() {
    int w = 200, h = 200;
    double radius = 0.4 * h;
    double deltaAng = 2. * M_PI / 12.;
    Canvas canvas(w, h);

    auto white = Color(1, 1, 1);

    auto p = Tuple::CreatePoint(0, 0, radius);
    p = Transforms::MakeRotateX(-M_PI / 2) * p;

    auto rotate = Transforms::MakeRotateZ(deltaAng);
    rotate.print();
    auto moveToCenter = Transforms::MakeTranslation(w / 2, h / 2, 0);
    auto moveToOrigin = moveToCenter.inverse();
    for (int i = 0; i < 12; i++) {
        p = moveToCenter * rotate * p;
        canvas.writePixel(round(p.x()), round(p.y()), white);
        p = moveToOrigin * p;
    }

    canvas.saveToPPM("clock");
}