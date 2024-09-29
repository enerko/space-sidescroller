#include "HealthBarUI.h"
#include <iostream>

HealthBarUI::HealthBarUI(Game* game):UIElement(game), Observer<float>(),
mHealthBarHeight(20.0f), mHealthBarWidth(200.0f), mHealthBarPos(Vector2(20,20)), mHealthPercentage(1.0f)
{
    std::cout << "Health Bar UI created" << std::endl;
}

HealthBarUI::~HealthBarUI()
{

}

void HealthBarUI::Draw(SDL_Renderer* renderer)
{
    DrawHealthOutline(renderer);
    DrawHealthFill(renderer);
    
}

void HealthBarUI::DrawHealthOutline(SDL_Renderer* renderer)
{
    // Draw Health Bar outline
    SDL_Rect r;

	r.w = static_cast<int>(mHealthBarWidth);
	r.h = static_cast<int>(mHealthBarHeight);

	// Center the rectangle around the position of the owner
	r.x = mHealthBarPos.x;
    r.y = mHealthBarPos.y;

    // Set the draw color
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); // Red color

    // Draw the rectangle outline
    SDL_RenderDrawRect(renderer, &r);
}

void HealthBarUI::DrawHealthFill(SDL_Renderer* renderer)
{
    // Draw health fill
    SDL_Rect fill;

    fill.w = static_cast<int>(mHealthBarWidth * mHealthPercentage);
	fill.h = static_cast<int>(mHealthBarHeight);

	// Center the rectangle around the position of the owner
	fill.x = mHealthBarPos.x;
    fill.y = mHealthBarPos.y;

    // Set the draw color
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); // Red color

    // Draw the rectangle outline
    SDL_RenderFillRect(renderer, &fill);
}

void HealthBarUI::Notify(const float& health)
{
    // Change health percentage
    // Draw is called every frame, so only have to change mHealthPercentage
    mHealthPercentage = health;
}