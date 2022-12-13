#pragma once
#include "Tuple.h"

// Chapter 2 exercise
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

void ThrowProjectile();