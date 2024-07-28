#include "HealthComponent.h"
#include "Subject.h"
#include <iostream>

// Any objects with health should add this component
HealthComponent::HealthComponent(Actor* owner):Component(owner), Subject<int>(),
mHealth(0)
{
    
}

void HealthComponent::TakeDamage(int damage)
{
    int health = GetHealth() - damage;
    SetHealth(health);
    NotifyObservers(health);
    std::cout << "Health: " << health << std::endl;
}

