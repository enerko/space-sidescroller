#include "GameOverMenu.h"
#include "Constants.h"
#include "TextComponent.h"

GameOverMenu::GameOverMenu(Game* game)
{
    // Create a black texture
    SDL_Texture* blackTexture = SDL_CreateTexture(game->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, ScreenWidth, ScreenHeight);
    mImage = new UIImage(game, blackTexture);
    mText = new TextComponent(game, "Game Over!");
}

GameOverMenu::~GameOverMenu()
{
   mImage -> Close();
   mText -> Close();
}
