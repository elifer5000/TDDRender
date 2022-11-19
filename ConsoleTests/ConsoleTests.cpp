// ConsoleTests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Tuple.h"
#include "Canvas.h"

struct Projectile {
    Tuple position;
    Tuple velocity;

    Projectile(Tuple pos, Tuple vel) : position(pos), velocity(vel) {
        _ASSERT(position.isPoint());
        _ASSERT(velocity.isVector());
    }
};

struct Environment {
    Tuple gravity;
    Tuple wind;

    Environment(Tuple _gravity, Tuple _wind) : gravity(_gravity), wind(_wind) {
        _ASSERT(gravity.isVector());
        _ASSERT(wind.isVector());
    }
};

Projectile tick(Environment& env, Projectile proj) {
    Tuple position = proj.position + proj.velocity;
    Tuple velocity = proj.velocity + env.gravity + env.wind;

    return Projectile(position, velocity);
}

int main()
{
    // projectile starts one unit above the origin.
    // velocity is normalized to 1 unit / tick.
    Projectile p(Tuple::CreatePoint(0.f, 1.f, 0.f), Tuple::CreateVector(1.f, 1.8f, 0.f).normalize() * 11.25);
    // gravity - 0.1 unit / tick, and wind is - 0.01 unit / tick.
    Environment env(Tuple::CreateVector(0.f, -0.1f, 0.f), Tuple::CreateVector(-0.01f, 0.f, 0.f));

    int w = 900, h = 550;
    Canvas canvas(w, h);
    int count = 0;
    int x, y;
    while (p.position.y > 0) {
        p = tick(env, p);
        x = round(p.position.x);
        y = round(p.position.y);
        std::cout << "Run " << ++count << ": Position: " << x << " " << y << " " << std::endl;// p.position.z << std::endl;
        canvas.writePixel(x, h - y, Color(1, 0, 0));
    }

    canvas.saveToPPM("projectile");
}
