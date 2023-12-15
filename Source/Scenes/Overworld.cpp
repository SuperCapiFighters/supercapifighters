//
// Created by Lucas N. Ferreira on 07/12/23.
//

#include "Overworld.h"
#include <vector>
#include <fstream>
#include <SDL2/SDL.h>
#include "../Game.h"
#include <string>
#include "../Components/DrawComponents/DrawAnimatedComponent.h"

Overworld::Overworld(Game* game)
        :Scene(game)
        ,mPlayer(nullptr)
{

}

Overworld::~Overworld()
{
//    delete mHUD;
}

void Overworld::Load()
{
    // Add background image located at Assets/Levels/Arena.png
    auto* background = new Actor(this);
    background->SetPosition(Vector2(0.0f, 0.0f));

    int mWindowWidth = mGame->GetWindowWidth();
    int mWindowHeight = mGame->GetWindowHeight();
    new DrawSpriteComponent(background, "../Assets/Sprites/Background.jpg", mWindowWidth, mWindowHeight);

    // Game Objects
    LoadData("../Assets/Map/ObjectsOneSoldier.csv");

    // Init HUD
//    mHUD = new HUD(this);

    // Play background music
    mGame->GetAudio()->PlaySound("MusicLoop.ogg", true);
}

void Overworld::LoadData(const std::string& fileName)
{
    int mWindowWidth = mGame->GetWindowWidth();
    int mWindowHeight = mGame->GetWindowHeight();

    Vector2 player1Position = Vector2(300.0f,mWindowHeight - 32.0f - 330.0f);
    Vector2 player2Position = Vector2(mWindowWidth - 300.0f,mWindowHeight - 32.0f - 330.0f);

    mPlayer2 = new Player(this, player2Position, 2, CharacterSelect::Vegeta);
    mPlayer2->SetPosition(player2Position);
    mPlayer1 = new Player(this, player1Position, 1, CharacterSelect::Goku);
    mPlayer1->SetPosition(player1Position);
}

void Overworld::EndFight() {
    mPlayer2->EndFight();
    mPlayer1->EndFight();
}

const Vector2& Overworld::GetCameraPos()
{
    return mPlayer->GetPosition();
}