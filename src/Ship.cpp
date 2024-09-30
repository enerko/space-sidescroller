#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "Game.h"
#include "Constants.h"

#include <iostream>

Ship::Ship(Game* game):Actor(game)
,mVerticalVel(0.0f)
{
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png"),
	};
	asc->SetAnimTextures(anims);

	mCol = new ColliderComponent(this);
	mCol->SetWidth(100);
    mCol->SetHeight(50);
}

void Ship::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	Vector2 pos = GetPosition();
	pos.y -= mVerticalVel * deltaTime;
	// Restrict position to the height of the screen
	
	if (pos.y < minScreenPosY)
	{
		pos.y = minScreenPosY;
	}
	else if (pos.y > maxScreenPosY)
	{
		pos.y = maxScreenPosY;
	}
	SetPosition(pos);
}

void Ship::ProcessKeyboard(const uint8_t* state)
{
	mVerticalVel = 0.0f;

	// up/down
	if (state[SDL_SCANCODE_S])
	{
		mVerticalVel -= 300.0f;
	}
	if (state[SDL_SCANCODE_W])
	{
		mVerticalVel += 300.0f;
	}
}
