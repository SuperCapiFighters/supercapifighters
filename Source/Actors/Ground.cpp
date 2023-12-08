//
// Created by julio on 10/11/23.
//

#include "Ground.h"
#include "../Game.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"


Ground::Ground(Game* game, Vector2 position)
        :Actor(game),
         mStartPosition(position)
{
    this->SetPosition(position);

    float width = game->GetWindowWidth();
    float heigth = game->GetWindowHeight() - position.y;
    mColliderComponent = new AABBColliderComponent(this, 0,0, width, heigth, ColliderLayer::Ground);
    mColliderComponent->SetEnabled(true);

    mRigidBodyComponent = new RigidBodyComponent(this, 10.0f, 1.0f, 1, true);

    std::vector<Vector2> vertices = {Vector2(0, 0), Vector2(width, 0), Vector2(width, heigth), Vector2(0, heigth)};
    mDrawPolygonComponent = new DrawPolygonComponent(this,0,0, width, heigth);
}