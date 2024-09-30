#pragma once
#include "UIPanel.h"
#include <vector>
#include "Math.h"
#include "SDL2/SDL.h"
#include "Observer.h"

class HealthBarUI : public UIElement
{
public:
    HealthBarUI(class Game* game, class HealthComponent* health);
    ~HealthBarUI();
    void Draw(SDL_Renderer* renderer) override;

private:
    Vector2 mHealthBarPos;
    float mHealthBarWidth;
    float mHealthBarHeight;

    class HealthComponent* mHealth;

    // Helper functions for the draw method
    void DrawHealthOutline(SDL_Renderer* renderer);
    void DrawHealthFill(SDL_Renderer* renderer, float healthPercentage);
};