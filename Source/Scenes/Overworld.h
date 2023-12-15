//
// Created by Lucas N. Ferreira on 07/12/23.
//

#pragma once

#include "../Actors/Player.h"
#include "Scene.h"
#include <string>
#include <vector>

class Overworld : public Scene {
  public:
    Overworld(class Game *game);
    ~Overworld();

    void EndFight();
    void Load() override;
    const Vector2 &GetCameraPos() override;

    //    class HUD *GetHUD() { return mHUD; }

  private:
    void LoadData(const std::string &fileName);

    class Player *mPlayer;
    //    class HUD *mHUD;

    // Game-specific
    class Player *mPlayer1;
    class Player *mPlayer2;
};
