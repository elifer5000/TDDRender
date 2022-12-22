#include <iostream>
#include "projectile.h"
#include "Canvas.h"
#include "Color.h"

Projectile tick(Environment& env, Projectile proj) {
    Tuple position = proj.m_position + proj.m_velocity;
    Tuple velocity = proj.m_velocity + env.m_gravity + env.m_wind;

    return Projectile(position, velocity);
}

void ThrowProjectile() {
    // projectile starts one unit above the origin.
   // velocity is normalized to 1 unit / tick.
    Projectile p(Tuple::CreatePoint(0.f, 1.f, 0.f), Tuple::CreateVector(1.f, 1.8f, 0.f).normalize() * 11.25);
    // gravity - 0.1 unit / tick, and wind is - 0.01 unit / tick.
    Environment env(Tuple::CreateVector(0.f, -0.1f, 0.f), Tuple::CreateVector(-0.01f, 0.f, 0.f));

    int w = 900, h = 550;
    Canvas canvas(w, h);
    int count = 0;
    int x, y;
    auto red = Color(1, 0, 0);
    while (p.m_position.y() > 0) {
        p = tick(env, p);
        x = round(p.m_position.x());
        y = round(p.m_position.y());
        std::cout << "Run " << ++count << ": Position: " << x << " " << y << " " << std::endl;// p.position.z << std::endl;
        canvas.writePixel(x, h - y, red);
    }

    canvas.saveToPPM("projectile");
}