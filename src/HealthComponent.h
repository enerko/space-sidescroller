#pragma once
#include "Component.h"
#include "Subject.h"

class HealthComponent : public Component, public Subject<float>
{
public:
    HealthComponent(Actor* owner, float health);
    void TakeDamage(float damage);

private:
    float mHealth;
    float mMaxHealth;
};