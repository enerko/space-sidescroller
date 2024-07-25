#include "Component.h"

class HealthComponent : public Component
{
public:
    int GetHealth(){ return mHealth; }

private:
    int mHealth;
};