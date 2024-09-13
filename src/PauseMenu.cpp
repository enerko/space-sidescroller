#include "PauseMenu.h"

PauseMenu::PauseMenu(Game* game)
{
    // create text
    mText = new TextComponent(game, "paused");
    std::cout << "Text created" << std::endl;
}

PauseMenu::~PauseMenu()
{
    mText -> Close();
}
