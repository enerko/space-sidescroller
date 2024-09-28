#include "GameOverMenu.h"
#include "Constants.h"

GameOverMenu::GameOverMenu(Game* game)
{
    // Create a black texture
    SDL_Texture* blackTexture = SDL_CreateTexture(game->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, ScreenWidth, ScreenHeight);
    mImage = new UIImage(game, blackTexture);
    mText = new TextComponent(game, "Game Over!");
    mButton = new UIButton(game, "Click Me", 200, 150, 200, 50, {255,255,255,255});

    mButton->SetOnClick([]() {
        std::cout << "Button was clicked!" << std::endl;
    });
}

GameOverMenu::~GameOverMenu()
{
   mImage -> Close();
   mText -> Close();
   mButton -> Close();
}

void GameOverMenu::Update(SDL_Event& e)
{
    // Handle events for the button
    mButton->HandleEvent(&e);
}
