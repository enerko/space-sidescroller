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

	class Ship* GetPlayer(){ return mPlayer; } 

	void AddUIElement(class UIElement* element);
	void RemoveUIElement(class UIElement* element);

	void HandleCollisions();

	bool IsGameOver(){ return mIsGameOver;}

	SDL_Renderer* GetRenderer(){return mRenderer;}

	void ResetGame();
	
	enum GameState
	{
		EGameplay,
		EPaused,
		EGameOver
	};

	void PlayerInput();

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	void LoadPanels(); // Helper function for LoadData
	
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

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	// Track if we're updating actors right now
	bool mUpdatingActors;

	// Game-specific
	class Ship* mPlayer; // Player's ship

	float mTimeSinceLastShot;
	float mShootInterval;

	bool mIsGameOver;

	class StateMachine* mStateMachine;
	GameState mGameState;

	class UIPanel* mPausePanel;
	class UIPanel* mGameOverPanel;
	class UIPanel* mInGamePanel;

	class HealthComponent* mHealth;
};
