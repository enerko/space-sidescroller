#pragma once
#include "Actor.h"
#include "SDL2/SDL_stdinc.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	float GetVerticalVelocity() const { return mVerticalVel; }
private:
	float mVerticalVel;
};