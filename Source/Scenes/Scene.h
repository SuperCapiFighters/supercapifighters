//
// Created by Lucas N. Ferreira on 07/12/23.
//

#pragma once

#include "../Math.h"
#include <SDL_stdinc.h>

class Scene {
  public:
    Scene(class Game *game);

    virtual void Load();
    virtual void ProcessInput(const Uint8 *keyState);
    virtual void EndFight(){};

    class Game *GetGame() { return mGame; }

    virtual const Vector2 &GetCameraPos();

  protected:
    class Game *mGame;
};
