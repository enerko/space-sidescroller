#include "Game.h"
#include "SDL2/SDL_image.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "BGSpriteComponent.h"
#include "Constants.h"
#include "Bullet.h"
#include "ColliderComponent.h"
#include "SDL2/SDL_ttf.h"
#include "UIPanel.h"
#include "HealthComponent.h"

#include <algorithm>
#include <iostream>

Game::Game():mWindow(nullptr)
,mRenderer(nullptr), mIsRunning(true), mUpdatingActors(false)
,mTimeSinceLastShot(0.0f), mShootInterval(5.0f), mGameState(EGameplay), mGameOverPanel(nullptr), mPausePanel(nullptr), mInGamePanel(nullptr)
{
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	mWindow = SDL_CreateWindow("Space Sidescroller", 100, 100, ScreenWidth, ScreenHeight, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	if (TTF_Init() == -1) {
        SDL_Log("Unable to initialize SDL_TTF: %s", SDL_GetError());
        return false;
    }


	LoadData();

	mTicksCount = SDL_GetTicks();
	
	return true;
}

void Game::RunLoop()
{	
	while (mIsRunning)
	{
		// start gameplay state
		
		ProcessInput();
		GenerateOutput();
		if (mGameState == EGameplay)
		{
			UpdateGame();
			PlayerInput();
		}

		if (mGameState == EGameOver)
		{
			std::cout << "GAMEOVER!" << std::endl;

			// TODO: this is called infinite times
			UnloadData();
		}
	}
}

void Game::PlayerInput()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// Process ship input
	mPlayer->ProcessKeyboard(state);
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
			
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_p)
                {
                    mGameState = (mGameState == EGameplay) ? EPaused : EGameplay;
					
                }
			default:
                // Delegate input to GameOverMenu if in GameOver state
                if (mGameState == EGameOver)
                {
                    mGameOverPanel->ProcessInput(event);  // Delegate event to GameOverMenu
                }
                break;
        	
		}
	}
	
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

void Game::UpdateGame()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// Update time since last bullet was shot
	mTimeSinceLastShot += deltaTime;
	if (mTimeSinceLastShot >= mShootInterval)
	{
		mTimeSinceLastShot = 0.0f;
		Bullet* bullet = new Bullet(this);
	}

	// Update all actors
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	HandleCollisions();
	mUpdatingActors = false;

	// Move any pending actors to mActors
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// Add any dead actors to a temp vector
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// Delete dead actors (which removes them from mActors)
	for (auto actor : deadActors)
	{
		delete actor;
	}

	// Check if mPlayer is in the mActors list
    bool playerExists = false;
    for (auto actor : mActors)
    {
        if (actor == mPlayer)
        {
            playerExists = true;
            break;
        }
    }

    // If player is not in the actors list, set Game to GameOver
    if (!playerExists)
    {
        mGameState = EGameOver; 
    }


}

void Game::HandleCollisions()
{

	// Check collision of the bullets with the player's ship
	for (auto col: mColliders)
	{
		ColliderComponent* playerCol = mPlayer->GetCollider();

		// Bullet intersected with the player
		if (col != playerCol && col->Intersect(playerCol))
		{			
			// Later add damage component
			mHealth->TakeDamage(10);

			// Delete bullet
			col->GetOwner()->SetState(Actor::EDead);
		}
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
	
	// Draw all sprite components
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	for (auto collider: mColliders)
	{
		// Debug: draw colliders
		// collider->DrawCollider(mRenderer);
	}

	mGameOverPanel -> ShowPanel( mGameState == EGameOver);
	mPausePanel -> ShowPanel(mGameState == EPaused);
	mInGamePanel -> ShowPanel(mGameState == EGameplay);

	// TODO: Group up the panels into a vector

	if (mGameOverPanel != nullptr)
	{
		mGameOverPanel -> Draw(mRenderer);
	}

	if (mPausePanel != nullptr)
	{
		mPausePanel -> Draw(mRenderer);
	}

	if (mInGamePanel != nullptr)
	{
		mInGamePanel -> Draw(mRenderer);
	}



	SDL_RenderPresent(mRenderer);
}

void Game::LoadPanels()
{
	// Create a panel to be displayed when player dies
	mGameOverPanel = new UIPanel(this);
	
	SDL_Texture* blackTexture = SDL_CreateTexture(this->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, ScreenWidth, ScreenHeight);
	mGameOverPanel -> AddImage(this, blackTexture);
	mGameOverPanel -> AddText(this, "Game over!");
	
	mGameOverPanel -> AddButton(this, "Restart", 
			[this]() {  
				std::cout << "Button clicked, restarting game!" << std::endl;
				this->ResetGame();  // Call ResetGame() method
			},
			200, 150, 200, 50, {255, 0, 0, 255}  // Button position, size, color
		);

	// Create a panel to be displayed when paused
	mPausePanel = new UIPanel(this);
	mPausePanel -> AddText(this, "paused");

	// Create a UI Panel for in-game objects
	mInGamePanel = new UIPanel(this);
}

void Game::LoadData()
{
	LoadPanels();
	
	// Create player's ship
	mPlayer = new Ship(this);

	// Create a health component for the player and create a health bar UI
	mHealth = new HealthComponent(mPlayer, PlayerMaxHealth);
	mInGamePanel -> AddHealthBar(this, mHealth);

	mPlayer->SetPosition(Vector2(100.0f, 384.0f));
	mPlayer->SetScale(1.5f);

	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2(512.0f, 384.0f));
	// Create the "far back" background
	BGSpriteComponent* bg = new BGSpriteComponent(temp);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	std::vector<SDL_Texture*> bgtexs = {
		GetTexture("Assets/Farback01.png"),
		GetTexture("Assets/Farback02.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-100.0f);
	// Create the closer background
	bg = new BGSpriteComponent(temp, 50);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	bgtexs = {
		GetTexture("Assets/Stars.png"),
		GetTexture("Assets/Stars.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-200.0f);
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		std::cout << mActors.size() << std::endl;
		std::cout << "Clearing actors" << std::endl;
		delete mActors.back();
		mActors.pop_back();

	}

	// Destroy textures
	for (auto i : mTextures)
	{
		std::cout << "Clearing textures" << std::endl;
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	// Is the texture already in the map?
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		// Load from file
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Create texture from surface
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void Game::Shutdown()
{
	UnloadData();
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::ResetGame()
{
	std::cout << "Reset game" << std::endl; 
	mGameState = EPaused;
}

void Game::AddActor(Actor* actor)
{
	// If we're updating actors, need to add to pending
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	
	// Is it in pending actors?
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end() && actor->GetState() == Actor::EDead)
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for ( ;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Game::AddCollider(ColliderComponent* collider)
{
	mColliders.push_back(collider);
}

void Game::RemoveCollider(ColliderComponent* collider)
{
    auto iter = std::find(mColliders.begin(), mColliders.end(), collider);
    if (iter != mColliders.end())
    {
        mColliders.erase(iter);
    }
}



