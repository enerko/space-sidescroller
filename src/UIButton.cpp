#include "UIButton.h"

UIButton::UIButton(Game* game, const std::string& text, int x, int y, int width, int height, SDL_Color color = {255,255,255,255})
:UIElement(game), mGame(game), mRenderer(game -> GetRenderer()), onClick(nullptr), mMessage(text), mColor(color)
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
    mText -> Close();
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

bool UIButton::HandleEvent(SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event->button.x;
        int mouseY = event->button.y;

        // Check if mouse is inside the button area
        bool inside = (mouseX > mRect.x && mouseX < mRect.x + mRect.w &&
                       mouseY > mRect.y && mouseY < mRect.y + mRect.h);

        if (inside && event->button.button == SDL_BUTTON_LEFT) {
            if (onClick != nullptr) {
                onClick();
                
            }
            return true;
        }
    }
    return false;
}

void UIButton::SetOnClick(void (*callback)())
{
    onClick = callback;
    
}