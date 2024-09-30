#pragma once
#include "SDL2/SDL.h"
#include "Game.h"
#include "Constants.h"
#include "HealthComponent.h"
#include <iostream>
#include <vector>
#include <functional>
#include <SDL2/SDL_ttf.h>

class UIPanel
{
public:
    UIPanel(class Game* game);

    virtual ~UIPanel();

    // Initial set up should be done here
    void Draw(SDL_Renderer* renderer);

    // Updates happen here for input based elements
    void ProcessInput(SDL_Event& e);

    void ShowPanel(bool showPanel); // Show or hide panel

    void AddButton(Game* game, const std::string& text, std::function<void()> onClick, int x, int y, int width, int height, SDL_Color color);
    void AddText(Game* game, const std::string& text, 
    SDL_Color color = {255,255,255,255}, int pointSize = 100, int posX = ScreenWidth / 2, int posY = ScreenHeight / 2);
    void AddImage(Game* game, SDL_Texture* texture);

    void AddHealthBar(Game *game, HealthComponent* healthComponent);

protected:
    class Game* mGame;
    bool mIsPanelVisible;

    std::vector<class UIElement*> mUIElements;
    std::vector<class UIText*> mTexts;
    std::vector<class UIImage*> mImages;
};

class UIElement
{
public:
    UIElement(class Game* game);
    virtual ~UIElement();

    // Initial set up should be done here
    virtual void Draw(SDL_Renderer* renderer);

    // Updates happen here for input based elements
    virtual void ProcessInput(SDL_Event& e);

protected:
    class Game* mGame;
};

class UIButton : public UIElement {
public:
    UIButton(Game* game, const std::string& text, std::function<void()> onClick, int x, int y, int width, int height, SDL_Color color);
    ~UIButton();

    // Methods to handle rendering and events
    void Draw(SDL_Renderer* renderer);
    void ProcessInput(SDL_Event& e) override;
    bool HandleEvent(SDL_Event* event);
    void OnClick();        // Callback function for the button click

private:
    Game* mGame;
    SDL_Rect mRect;           // Button position and size
    SDL_Color mColor;         // Button background color
    SDL_Renderer* mRenderer;  // SDL renderer

    const std::string& mMessage;

    TTF_Font* mFont;          // Font for rendering text
    SDL_Texture* mTextTexture; // Texture for the button text

    std::function<void()> mOnClick;
    
};

class UIImage : public UIElement
{
public:
    UIImage(class Game* game, SDL_Texture* texture);
    ~UIImage();
    
    void Draw(SDL_Renderer* renderer) override;

private:
    SDL_Texture* mTexture;
};

class UIText : public UIElement
{
public:
    UIText(Game* game, const std::string& text, 
    SDL_Color color = {255,255,255,255}, int pointSize = 100, int posX = ScreenWidth / 2, int posY = ScreenHeight / 2);
    virtual ~UIText();

    void Draw(SDL_Renderer* renderer) override;

    SDL_Texture* LoadFont(int fontSize, const std::string& text, SDL_Color& color);

    void Display(SDL_Renderer* renderer) const;

protected:
    class Game* mGame;
    mutable SDL_Rect mTextRect;
    SDL_Texture* mTextTexture;
    const std::string& mText;
    int mPointSize;
    SDL_Color mColor;
};