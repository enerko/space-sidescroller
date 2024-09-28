#pragma once
#include "UIElement.h"
#include "TextComponent.h"
#include "UIImage.h"
#include "Game.h"

class GameOverMenu
{
public:
    GameOverMenu(class Game* game);
    virtual ~GameOverMenu();
    
private:
    TextComponent* mText;
    Game* mGame;
    UIImage* mImage;
};