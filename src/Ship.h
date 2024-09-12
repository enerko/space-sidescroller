#pragma once
#include "Actor.h"
#include "SDL2/SDL_stdinc.h"
#include "ColliderComponent.h"
#include "HealthComponent.h"
#include "HealthBarUI.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	float GetVerticalVelocity() const { return mVerticalVel; }
	ColliderComponent* GetCollider(){ return mCol; }
	HealthComponent* GetHealthComponent(){ return mHealth; }
private:
	float mVerticalVel;
	ColliderComponent* mCol;
	HealthComponent* mHealth;
	HealthBarUI* mHealthUI;
};