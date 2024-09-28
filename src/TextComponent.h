#pragma once
#include "UIElement.h"
#include "Constants.h"
#include <iostream>

class TextComponent:public UIElement
{
public:
    TextComponent(Game* game, const std::string& text, 
    SDL_Color color = {255,255,255,255}, int pointSize = 100, int posX = ScreenWidth / 2, int posY = ScreenHeight / 2);
    virtual ~TextComponent();

    virtual void Draw(SDL_Renderer* renderer);

    SDL_Texture* LoadFont(int fontSize, const std::string& text, SDL_Color& color);

    void Display(SDL_Renderer* renderer) const;

protected:
    class Game* mGame;
    UIState mState;
    mutable SDL_Rect mTextRect;
    SDL_Texture* mTextTexture;
    const std::string& mText;
    int mPointSize;
    SDL_Color mColor;
};