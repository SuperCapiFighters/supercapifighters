//
// Created by samuel on 15/12/23.
//

#include "DrawHealthBar.h"
#include "../../Actors/Actor.h"
#include "../../Game.h"

DrawHealthBar::DrawHealthBar(class Actor *owner,bool reverse, int dx, int dy, int width, int height, int drawOrder)
        : DrawComponent(owner,drawOrder),mReverse(reverse), mDx(dx),mDy(dy),mWidth(width),mHeight(height){

}

void DrawHealthBar::Draw(SDL_Renderer *renderer) {
    SDL_Rect healthBarRect;
    healthBarRect.y = mDy;
    healthBarRect.h = mHeight;
    int width = (mOwner->GetHeart()*1.0f/mOwner->GetMaxHeart()*1.0f) *mWidth;
    if(mOwner->GetHeart()<0){
        width = 0;
    }

    if(mReverse){
        healthBarRect.x = mDx;
        healthBarRect.w = width;
    }else{
        healthBarRect.x = mDx+mWidth-width;
        healthBarRect.w = width;
    }





    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Cor verde
    SDL_RenderFillRect(renderer, &healthBarRect);

}