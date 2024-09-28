#pragma once
#include "UIElement.h"
#include "TextComponent.h"
#include "UIButton.h"
#include "UIImage.h"
#include "Game.h"

class GameOverMenu
{
public:
    GameOverMenu(class Game* game);
    virtual ~GameOverMenu();

    void Update(SDL_Event& e);
    
private:
    TextComponent* mText;
    Game* mGame;
    UIImage* mImage;
    UIButton* mButton;
    TextComponent* mButtonText;
};