#pragma once
#include "SDL2/SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	
	SDL_Texture* GetTexture(const std::string& fileName);

	void AddCollider(class ColliderComponent* collider);
	void RemoveCollider(class ColliderComponent* collider);

	std::vector<class ColliderComponent*> GetColliders(){ return mColliders; }

	class Ship* GetPlayer(){ return mShip; } 
	class HealthBarUI* GetHealthBar() { return mHealthBar; }

	void AddUIElement(class UIElement* element);
	void RemoveUIElement(class UIElement* element);

	void HandleCollisions();
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
	
	// Map of textures loaded
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// All the actors in the game
	std::vector<class Actor*> mActors;
	// Any pending actors
	std::vector<class Actor*> mPendingActors;

	// All the sprite components drawn
	std::vector<class SpriteComponent*> mSprites;
	
	// All the colliders
	std::vector<class ColliderComponent*> mColliders;

	// All the UI elements
	std::vector<class UIElement*> mUIElements;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	// Track if we're updating actors right now
	bool mUpdatingActors;

	// Game-specific
	class Ship* mShip; // Player's ship

	float mTimeSinceLastShot;
	float mShootInterval;

	class HealthBarUI* mHealthBar;
};
