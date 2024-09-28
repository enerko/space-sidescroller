#include "Game.h"
#include "UIImage.h"
#include "Constants.h"
#include <iostream>

UIImage::UIImage(Game* game, SDL_Texture* texture)
:UIElement(game), mTexture(texture)
{

}

UIImage::~UIImage()
{

}

void UIImage::Draw(SDL_Renderer* renderer)
{
    SDL_Rect dstRect;
    SDL_QueryTexture(mTexture, nullptr, nullptr, &dstRect.w, &dstRect.h);
    dstRect.x = 0;
    dstRect.y = 0;
        
    SDL_RenderCopy(renderer, mTexture, nullptr, &dstRect);
}