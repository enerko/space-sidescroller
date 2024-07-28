#include "UIElement.h"
#include <vector>
#include "Math.h"
#include "SDL2/SDL.h"
#include "Observer.h"

class HealthBarUI : public UIElement, public Observer<int>
{
public:
    HealthBarUI(class Game* game);
    ~HealthBarUI();
    void Draw(SDL_Renderer* renderer);

    // Get updates for every time health changes
    void Notify(const int& health) override;

    void Update(int health);

private:
    Vector2 mHealthBarPos;
    float mHealthBarWidth;
    float mHealthBarHeight;
};