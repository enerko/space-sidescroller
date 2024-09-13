#include "UIElement.h"
#include "Game.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>

UIElement::UIElement(Game* game)
    : mGame(game)
    , mState(EActive)
{
    game->AddUIElement(this);
}

UIElement::~UIElement()
{
    // TODO
}

void UIElement::Draw(SDL_Renderer* renderer)
{
    // Default implementation does nothing
    // Derived classes should override this method
}

void UIElement::Update()
{
    // Default implementation does nothing
    // Derived classes should override this method
}

void UIElement::Close()
{
    mState = EClosed;
}

