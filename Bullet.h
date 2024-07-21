
#include "Actor.h"
#include "SDL2/SDL_stdinc.h"
#include "ColliderComponent.h"

class Bullet : public Actor
{
public:
	Bullet(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const Uint8* state);
	float GetSpeed() const { return mBulletSpeed; }
	
private:
	float mBulletSpeed;
	Vector2 mBulletPosition;
	ColliderComponent* mCol;
};