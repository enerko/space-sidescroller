#pragma once

#include "Game.h"
#include "Actor.h"
#include "Component.h"
#include "SDL2/SDL.h"

class ColliderComponent: public Component
{
public: 
    ColliderComponent(class Actor* owner);
    ~ColliderComponent();

    // Set width, height, offset
    void SetWidth(float width);
    void SetHeight(float height);
    void SetOffset(Vector2 offset);

    // Draw collider for debugging purposes
    void DrawCollider(SDL_Renderer* renderer);

    Vector2 GetMin();
    Vector2 GetMax();

    bool Intersect(ColliderComponent* b);

private:
    float mWidth;
    float mHeight;
    Vector2 mOffset;
};

