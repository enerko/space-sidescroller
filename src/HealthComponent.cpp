#include "HealthComponent.h"
#include "Subject.h"
#include "Actor.h"
#include <iostream>

// Any objects with health should add this component
HealthComponent::HealthComponent(Actor* owner, float health)
:Component(owner), mOwner(owner)
{
    mMaxHealth = mHealth = health;
}

float HealthComponent::GetHealthPercentage()
{
    return static_cast<float>(mHealth) / static_cast<float>(mMaxHealth);
}

void HealthComponent::TakeDamage(float damage)
{
    mHealth -= damage;

    if (mHealth <= 0)
    {
        mOwner->SetState(Actor::EDead);
    }
}