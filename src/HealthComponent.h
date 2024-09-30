#pragma once
#include "Component.h"
#include "Subject.h"

class HealthComponent : public Component
{
public:
    HealthComponent(Actor* owner, float health);
    void TakeDamage(float damage);
    float GetHealthPercentage();

private:
    float mHealth;
    float mMaxHealth;
    class Actor* mOwner;
};