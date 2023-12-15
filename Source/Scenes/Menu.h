//
// Created by Lucas N. Ferreira on 07/12/23.
//

#pragma once

#include "Scene.h"

class Menu : public Scene
{
public:
    Menu(class Game* game);

    void Load() override;
    void ProcessInput(const Uint8* keyState) override;

private:
//    class Font *mMenuFont;
};
