#include "HealthComponent.h"
#include <iostream>

HealthComponent::HealthComponent(Actor* owner):Component(owner), 
mHealth(0)
{

}

void HealthComponent::TakeDamage(int damage)
{
    int health = GetHealth() - damage;
    SetHealth(health);
    std::cout << "Health: " << health << std::endl;
}

