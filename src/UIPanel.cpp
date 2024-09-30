#include "Game.h"
#include "UIPanel.h"
#include "Constants.h"
#include "HealthBarUI.h"
#include <iostream>

UIPanel::UIPanel(class Game* game)
: mIsPanelVisible(false)
{};
UIPanel::~UIPanel()
{
    while (!mUIElements.empty())
	{
		delete mUIElements.back();
		mUIElements.pop_back();
	}
};

void UIPanel::ShowPanel(bool showPanel)
{
    mIsPanelVisible = showPanel;
}

void UIPanel::Draw(SDL_Renderer* renderer)
{
    if (mIsPanelVisible)
    {
        for (auto element : mUIElements)
        {
            element -> Draw(renderer);
        }
    }
}

void UIPanel::ProcessInput(SDL_Event& e)
{
    for (auto element : mUIElements)
    {
        element -> ProcessInput(e);
    }

}

void UIPanel::AddButton(Game* game, const std::string& text, std::function<void()> onClick, int x, int y, int width, int height, SDL_Color color)
{
    UIButton* newButton = new UIButton(game, text, onClick, x, y, width, height, color);
    mUIElements.push_back(newButton);
}

void UIPanel::AddText(Game* game, const std::string& text, SDL_Color color, int fontSize, int posX, int posY)
{
    UIText* newText = new UIText(game, text, color, fontSize, posX, posY);
    mUIElements.push_back(newText);
}

void UIPanel::AddImage(Game* game, SDL_Texture* texture)
{
    UIImage* newImage = new UIImage(game, texture);
    mUIElements.push_back(newImage);
}

void UIPanel::AddHealthBar(Game* game, HealthComponent* healthComponent)
{
    HealthBarUI* healthBar = new HealthBarUI(game, healthComponent);
    mUIElements.push_back(healthBar);
}

UIElement::UIElement(Game* game)
    : mGame(game)
{
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

void UIElement::ProcessInput(SDL_Event& e)
{
    // Default implementation does nothing
    // Derived classes should override this method
}



// Button class
UIButton::UIButton(Game* game, const std::string& text, std::function<void()> onClick, int x, int y, int width, int height, SDL_Color color = {255,255,255,255})
:UIElement(game), mGame(game), mRenderer(game -> GetRenderer()), mOnClick(onClick), mMessage(text), mColor(color)
{
    mRect = {x, y, width, height};   // Set position and size

    // Load font
    mFont = TTF_OpenFont("Assets/Carlito-Regular.ttf", 24);
    if (!mFont) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    // Create text texture
    SDL_Surface* surface = TTF_RenderText_Solid(mFont, mMessage.c_str(), {0, 0, 0, 255}); // White text
    if (!surface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return;
    }

    mTextTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface);
}

UIButton::~UIButton()
{
    // Check if mTextTexture is valid, then destroy it
    if (mTextTexture != nullptr)
    {
        SDL_DestroyTexture(mTextTexture);
        mTextTexture = nullptr; // Set to nullptr to avoid dangling pointers
    }
}

void UIButton::Draw(SDL_Renderer* renderer)
{
    // Set the color for the button background and draw the button
    SDL_SetRenderDrawColor(renderer, mColor.r, mColor.g, mColor.b, mColor.a);
    SDL_RenderFillRect(renderer, &mRect);

    // Render the text on top of the button
    int textWidth, textHeight;
    SDL_QueryTexture(mTextTexture, nullptr, nullptr, &textWidth, &textHeight);

    SDL_Rect textRect = {mRect.x + (mRect.w - textWidth) / 2, 
                         mRect.y + (mRect.h - textHeight) / 2, 
                         textWidth, textHeight};

    SDL_RenderCopy(renderer, mTextTexture, nullptr, &textRect);
}

void UIButton::ProcessInput(SDL_Event& e)
{
    // Handle events for the button
    HandleEvent(&e);
}

bool UIButton::HandleEvent(SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event->button.x;
        int mouseY = event->button.y;

        // Check if mouse is inside the button area
        bool inside = (mouseX > mRect.x && mouseX < mRect.x + mRect.w &&
                       mouseY > mRect.y && mouseY < mRect.y + mRect.h);

        if (inside && event->button.button == SDL_BUTTON_LEFT) {
            OnClick();
            return true;
        }
    }
    return false;
}

void UIButton::OnClick()
{
	// Call attached handler, if it exists
	if (mOnClick)
	{
		mOnClick();
	}
}

// Image class
UIImage::UIImage(Game* game, SDL_Texture* texture)
:UIElement(game), mTexture(texture)
{

}

UIImage::~UIImage()
{
    // Check if mTexture is valid, and destroy it
    if (mTexture != nullptr)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;  // Set to nullptr to avoid dangling pointers
    }
}

void UIImage::Draw(SDL_Renderer* renderer)
{
    SDL_Rect dstRect;
    SDL_QueryTexture(mTexture, nullptr, nullptr, &dstRect.w, &dstRect.h);
    dstRect.x = 0;
    dstRect.y = 0;
        
    SDL_RenderCopy(renderer, mTexture, nullptr, &dstRect);
}

// Text class
UIText::UIText(Game* game, const std::string& text, 
SDL_Color color, int fontSize, int posX, int posY)
:UIElement(game), mGame(game), mText(text), mTextRect{posX, posY, 0, 0}
{
    mTextTexture = LoadFont(fontSize, text, color);
    SDL_QueryTexture(mTextTexture, nullptr, nullptr, &mTextRect.w, &mTextRect.h);
    mTextRect.x = posX - mTextRect.w / 2; // Center horizontally
    mTextRect.y = posY - mTextRect.h / 2; // Center vertically
}

UIText::~UIText()
{
    // Check if mTextTexture is valid, then destroy it
    if (mTextTexture != nullptr)
    {
        SDL_DestroyTexture(mTextTexture);
        mTextTexture = nullptr; // Set to nullptr to avoid dangling pointers
    }
}

void UIText::Draw(SDL_Renderer* renderer)
{
    Display(renderer);
}

void UIText::Display(SDL_Renderer* renderer) const
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

SDL_Texture* UIText::LoadFont(int fontSize, 
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