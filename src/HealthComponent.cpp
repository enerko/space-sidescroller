#include "HealthComponent.h"
#include "Subject.h"
#include "Actor.h"
#include <iostream>

// Any objects with health should add this component
HealthComponent::HealthComponent(Actor* owner, float health)
:Component(owner), Subject<float>(), mOwner(owner)
{
    mMaxHealth = mHealth = health;
}

void HealthComponent::TakeDamage(float damage)
{
    mHealth -= damage;

    // Notify the health percentage to the UI
    NotifyObservers(static_cast<float>(mHealth / mMaxHealth));

    if (mHealth <= 0)
    {
        mOwner->SetState(Actor::EDead);
    }
}