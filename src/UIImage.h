#pragma once
#include "UIElement.h"

class UIImage:public UIElement
{
public:
    UIImage(class Game* game, SDL_Texture* texture);
    ~UIImage();
    virtual void Draw(SDL_Renderer* renderer);

private:
    SDL_Texture* mTexture;
};