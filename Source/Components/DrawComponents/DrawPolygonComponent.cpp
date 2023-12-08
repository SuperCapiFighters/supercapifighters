//
// Created by Lucas N. Ferreira on 28/09/23.
//

#include "DrawPolygonComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game.h"

DrawPolygonComponent::DrawPolygonComponent(class Actor* owner,int dx, int dy, int width, int height, int drawOrder)
        :DrawComponent(owner)
        ,mDrawOrder(drawOrder)
        ,mDraw(true)
{
    mVertices = {Vector2(-width/2 + dx, -height/2-dy), Vector2(width/2+dx, -height/2 -dy), Vector2(width/2 +dx, height/2-dy), Vector2(-width/2 +dx, height/2-dy)};
}

void DrawPolygonComponent::Draw(SDL_Renderer *renderer)
{
    if(!mDraw) return;
    // Set draw color to green
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    Vector2 pos = mOwner->GetPosition();
    Vector2 cameraPos = mOwner->GetGame()->GetCameraPos();

    // Render vertices as lines
    for(int i = 0; i < mVertices.size() - 1; i++) {
        SDL_RenderDrawLine(renderer, pos.x + mVertices[i].x - cameraPos.x,
                                     pos.y + mVertices[i].y - cameraPos.y,
                                     pos.x + mVertices[i+1].x - cameraPos.x,
                                     pos.y + mVertices[i+1].y - cameraPos.y);
    }

    // Close geometry
    SDL_RenderDrawLine(renderer, pos.x + mVertices[mVertices.size() - 1].x - cameraPos.x,
                                 pos.y + mVertices[mVertices.size() - 1].y - cameraPos.y,
                                 pos.x + mVertices[0].x - cameraPos.x,
                                 pos.y + mVertices[0].y - cameraPos.y);
}

void DrawPolygonComponent::Update(int width, int height) {
    std::vector<Vector2> vertices = {Vector2(0, 0), Vector2(width, 0), Vector2(width, height), Vector2(0, height)};
    mVertices = vertices;

}