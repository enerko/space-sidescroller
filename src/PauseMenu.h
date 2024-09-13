#pragma once
#include "UIElement.h"
#include "TextComponent.h"
#include "Game.h"

class PauseMenu
{
public:
    PauseMenu(class Game* game);
    virtual ~PauseMenu();
    
private:
    TextComponent* mText;
    Game* mGame;
};