#include "HealthBarUI.h"
#include <iostream>

HealthBarUI::HealthBarUI(Game* game):UIElement(game), Observer<int>(),
mHealthBarHeight(50.0f), mHealthBarWidth(100.0f), mHealthBarPos(Vector2(50,50))
{
    std::cout << "Health Bar UI created" << std::endl;
}

HealthBarUI::~HealthBarUI()
{

}

void HealthBarUI::Draw(SDL_Renderer* renderer)
{
    SDL_Rect r;

	r.w = static_cast<int>(mHealthBarWidth);
	r.h = static_cast<int>(mHealthBarHeight);

	// Center the rectangle around the position of the owner
	r.x = mHealthBarPos.x;
    r.y = mHealthBarPos.y;

    // Set the draw color
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); // White color

    // Draw the rectangle outline
    SDL_RenderDrawRect(renderer, &r);
}

void HealthBarUI::Notify(const int& health)
{
    std::cout << "HealthBarUI: Notify called with health: " << health << std::endl;
    Update(health);
}


void HealthBarUI::Update(int health)
{
    // TODO: change health UI
    std::cout << "Health:" << health << std::endl;
}