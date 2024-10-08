#include "Bullet.h"
#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Constants.h"
#include "Ship.h"

#include <random>
#include <iostream>
#include <cstdlib>   
#include <ctime>     

// Bullet must be drawn, updated position, check for collision?
Bullet::Bullet(Game* game)
	:Actor(game)
	,mBulletSpeed(200.0f)
	,mBulletPosition(ScreenWidth,0)
{
	// Create an animated sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	SDL_Texture* tex = (game->GetTexture("Assets/Laser.png"));
	if (!tex) {
    	SDL_Log("Failed to load texture: Assets/Laser.png");
	}
	sc->SetTexture(tex);

	// Spawn bullet within valid range
	int num = (rand() % (maxScreenPosY - minScreenPosY + 1)) + minScreenPosY;
    SetPosition(Vector2(ScreenWidth, static_cast<float>(num)));

	// Create a collider component
	mCol = new ColliderComponent(this);
	mCol->SetWidth(30);
    mCol->SetHeight(20);
}

void Bullet::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	Vector2 pos = GetPosition();

	// Only travels horizontally
	pos.x -= mBulletSpeed * deltaTime;

	SetPosition(pos);

}
