#pragma once
#include "Component.h"

class HealthComponent : public Component
{
public:
    HealthComponent(Actor* owner);
    int GetHealth(){ return mHealth; }
    void SetHealth(int health){ mHealth = health; }
    void TakeDamage(int damage);

private:
    int mHealth;
};