#include "HealthBarUI.h"
#include "HealthComponent.h"
#include <iostream>

HealthBarUI::HealthBarUI(Game* game, HealthComponent* health)
:UIElement(game), 
mHealthBarHeight(20.0f), mHealthBarWidth(200.0f), mHealthBarPos(Vector2(20,20)), mHealth(health)
{
    // Create a health bar UI that is tied to a health component attached to an actor
    std::cout << "Health Bar UI created" << std::endl;
}

HealthBarUI::~HealthBarUI()
{

}

void HealthBarUI::Draw(SDL_Renderer* renderer)
{
    DrawHealthOutline(renderer);
    DrawHealthFill(renderer, mHealth->GetHealthPercentage());  
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

void HealthBarUI::DrawHealthFill(SDL_Renderer* renderer, float healthPercentage)
{
    // Draw health fill
    SDL_Rect fill;

    fill.w = static_cast<int>(mHealthBarWidth * healthPercentage);
	fill.h = static_cast<int>(mHealthBarHeight);

	// Center the rectangle around the position of the owner
	fill.x = mHealthBarPos.x;
    fill.y = mHealthBarPos.y;

    // Set the draw color
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); // Red color

    // Draw the rectangle outline
    SDL_RenderFillRect(renderer, &fill);
}