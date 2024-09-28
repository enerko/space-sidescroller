#pragma once
#include "UIElement.h"
#include "Game.h"
#include "TextComponent.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>

class UIButton:public UIElement {
public:
    UIButton(Game* game, const std::string& text, int x, int y, int width, int height, SDL_Color color);
    ~UIButton();

    // Methods to handle rendering and events
    void Draw(SDL_Renderer* renderer);
    bool HandleEvent(SDL_Event* event);
    
    // Set the callback for when the button is pressed
    void SetOnClick(void (*callback)());

private:
    Game* mGame;
    SDL_Rect mRect;           // Button position and size
    SDL_Color mColor;         // Button background color
    SDL_Renderer* mRenderer;  // SDL renderer

    TextComponent* mText;        // Button text
    const std::string& mMessage;

    TTF_Font* mFont;          // Font for rendering text
    SDL_Texture* mTextTexture; // Texture for the button text

    void (*onClick)();        // Callback function for the button click
};