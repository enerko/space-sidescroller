#include "ColliderComponent.h"
#include <iostream>

ColliderComponent::ColliderComponent(Actor* owner) : Component(owner), 
mWidth(0.0f), mHeight(0.0f), mOffset(0,0)
{
    mOwner->GetGame()->AddCollider(this);
}

ColliderComponent::~ColliderComponent()
{
    mOwner->GetGame()->RemoveCollider(this);
}


void ColliderComponent::SetWidth(float width)
{
    mWidth = width;
}
void ColliderComponent::SetHeight(float height)
{
    mHeight = height;
}

void ColliderComponent::SetOffset(Vector2 offset)
{
    mOffset = offset;
}

void ColliderComponent::DrawCollider(SDL_Renderer* renderer)
{
    SDL_Rect r;

	r.w = static_cast<int>(mWidth);
	r.h = static_cast<int>(mHeight);

	// Center the rectangle around the position of the owner
	r.x = GetMin().x;
    r.y = GetMin().y;

    // Set the draw color
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color

    // Draw the rectangle outline
    SDL_RenderDrawRect(renderer, &r);
}

// Get minimum point (top left)
Vector2 ColliderComponent::GetMin()
{
    Vector2 newMin;
    newMin.x = mOwner->GetPosition().x - mWidth / 2 + mOffset.x;
    newMin.y = mOwner->GetPosition().y - mHeight / 2 + mOffset.y;

    return newMin;
}

// Get maximum point (bottom right)
Vector2 ColliderComponent::GetMax()
{
    Vector2 newMax;
    newMax.x = mOwner->GetPosition().x + mWidth / 2 + mOffset.x;
    newMax.y = mOwner->GetPosition().y + mHeight / 2 + mOffset.y;

    return newMax;
}

// AABB vs AABB Intersection test
bool ColliderComponent::Intersect(ColliderComponent* b)
{
    bool noIntersect = GetMax().x < b->GetMin().x ||
        GetMax().y < b->GetMin().y ||
        b->GetMax().x < GetMin().x ||
        b->GetMax().y < GetMin().y;
    return !noIntersect;
}