#pragma once
#include "Tuple.h"

// Chapter 2 exercise
struct Projectile {
    Tuple m_position;
    Tuple m_velocity;

    Projectile(Tuple pos, Tuple vel) : m_position(pos), m_velocity(vel) {
        _ASSERT(m_position.isPoint());
        _ASSERT(m_velocity.isVector());
    }
};

struct Environment {
    Tuple m_gravity;
    Tuple m_wind;

    Environment(Tuple gravity, Tuple wind) : m_gravity(gravity), m_wind(wind) {
        _ASSERT(m_gravity.isVector());
        _ASSERT(m_wind.isVector());
    }
};

void ThrowProjectile();