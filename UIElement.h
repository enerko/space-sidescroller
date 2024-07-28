#include "SDL2/SDL.h"

class UIElement
{
public:
    UIElement(class Game* game);
    virtual ~UIElement();

    // Initial set up should be done here
    virtual void Draw(SDL_Renderer* renderer);

    // Updates happen here (like health)
    virtual void Update();

    enum UIState { EActive, EClosed };
    void Close();
    UIState GetState() const { return mState; }

protected:
    class Game* mGame;
    UIState mState;
};