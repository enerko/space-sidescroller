#include "UIPanel.h"
#include <vector>
#include "Math.h"
#include "SDL2/SDL.h"
#include "Observer.h"

class HealthBarUI : public UIElement, public Observer<float>
{
public:
    HealthBarUI(class Game* game);
    ~HealthBarUI();
    void Draw(SDL_Renderer* renderer);

    // Get updates for every time health changes
    void Notify(const float& health) override;

private:
    Vector2 mHealthBarPos;
    float mHealthBarWidth;
    float mHealthBarHeight;
    float mHealthPercentage;

    // Helper functions for the draw method
    void DrawHealthOutline(SDL_Renderer* renderer);
    void DrawHealthFill(SDL_Renderer* renderer);
};