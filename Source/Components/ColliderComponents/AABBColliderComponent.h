//
// Created by Lucas N. Ferreira on 28/09/23.
//

#pragma once
#include "../Component.h"
#include "../../Math.h"
#include "../RigidBodyComponent.h"
#include <vector>
#include <set>

enum class ColliderLayer
{
    Ground,
    Player1,
    Player2,
    Punch,
    Defense
};

enum class CollisionSide
{
    Top,
    Down,
    Left,
    Right
};

class AABBColliderComponent : public Component
{
public:
    struct Overlap
    {
        float amount;
        CollisionSide side;
        AABBColliderComponent *target;
    };

    AABBColliderComponent(class Actor* owner, int dx, int dy, int w, int h,
                                ColliderLayer layer, int updateOrder = 10);
    ~AABBColliderComponent() override;

    bool Intersect(const AABBColliderComponent& b) const;
    void DetectCollision(RigidBodyComponent *rigidBody);

    Vector2 GetMin() const;
    Vector2 GetMax() const;
    Vector2 GetCenter() const;
    ColliderLayer GetLayer() const { return mLayer; }

    void SetSize(int width, int height) {
        mWidth = width;
        mHeight = height;
    }

    float GetWidth() const { return mWidth; }
    float GetHeight() const { return mHeight; }

private:
    Overlap GetMinOverlap(AABBColliderComponent* b) const;
    void ResolveCollisions(RigidBodyComponent *rigidBody, const Overlap& minOverlap);

    Vector2 mOffset;
    int mWidth;
    int mHeight;

    ColliderLayer mLayer;
};