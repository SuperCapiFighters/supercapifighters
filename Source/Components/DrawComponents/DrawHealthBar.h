//
// Created by samuel on 15/12/23.
//
#include "DrawComponent.h"
#include <string>

#ifndef SUPER_CAPI_FIGHTERS_DRAWHEALTHBAR_H
#define SUPER_CAPI_FIGHTERS_DRAWHEALTHBAR_H

class DrawHealthBar : public DrawComponent{
public:
    DrawHealthBar(class Actor* owner,bool reverse,int dx,int dy,int width = 10,int height = 10, int drawOrder=110);
    void Draw(SDL_Renderer* renderer) override;

private:
    int mWidth;
    int mHeight;
    int mDx;
    int mDy;
    bool mReverse;


};

#endif //SUPER_CAPI_FIGHTERS_DRAWHEALTHBAR_H
