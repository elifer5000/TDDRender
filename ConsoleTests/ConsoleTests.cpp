// ConsoleTests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Tuple.h"

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
    Projectile p(Tuple::CreatePoint(0.f, 1.f, 0.f), Tuple::CreateVector(1.f, 1.f, 0.2f).normalize());
    // gravity - 0.1 unit / tick, and wind is - 0.01 unit / tick.
    Environment env(Tuple::CreateVector(0.f, -0.1f, 0.f), Tuple::CreateVector(-0.01f, 0.f, 0.f));

    int count = 0;
    while (p.position.y > 0) {
        p = tick(env, p);
        std::cout << "Run " << ++count << ": Position: " << p.position.x << " " << p.position.y << " " << p.position.z << std::endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
