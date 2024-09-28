#include "TextComponent.h"
#include <SDL2/SDL_ttf.h>
#include "Game.h"

TextComponent::TextComponent(Game* game, const std::string& text, 
SDL_Color color, int fontSize, int posX, int posY)
:UIElement(game)
, mGame(game), mText(text), mTextRect{posX, posY, 0, 0}
{
    mTextTexture = LoadFont(fontSize, text, color);
    SDL_QueryTexture(mTextTexture, nullptr, nullptr, &mTextRect.w, &mTextRect.h);
    mTextRect.x = posX - mTextRect.w / 2; // Center horizontally
    mTextRect.y = posY - mTextRect.h / 2; // Center vertically
}

TextComponent::~TextComponent()
{
    std::cout << "Text deleted" << std::endl;
}

void TextComponent::Draw(SDL_Renderer* renderer)
{
    Display(renderer);
}

void TextComponent::Display(SDL_Renderer* renderer) const
{
    // Ensure that the texture is valid before attempting to draw
    if (mTextTexture != nullptr)
    {
        // Copy the texture to the renderer at the specified position and size
        SDL_RenderCopy(renderer, mTextTexture, nullptr, &mTextRect);
    }
    else
    {
        std::cerr << "Text texture is null. Cannot draw." << std::endl;
    }
}

SDL_Texture* TextComponent::LoadFont(int fontSize, 
const std::string& text, SDL_Color& color)
{
    TTF_Font* font = TTF_OpenFont("Assets/Carlito-Regular.ttf", fontSize);
    if (!font)
    {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }

    // Render text to surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!textSurface)
    {
        std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
    }

    // Convert surface to texture
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mGame -> GetRenderer(), textSurface);
    if (!textTexture)
    {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        SDL_DestroyTexture(textTexture);
    }

    // Free surface and return font
    SDL_FreeSurface(textSurface);
    return textTexture;
}