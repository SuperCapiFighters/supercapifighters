//
// Created by Lucas N. Ferreira on 07/12/23.
//

#include "Menu.h"
#include "../Game.h"
//#include "../Font.h"
#include "../Actors/Actor.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"
//#include "../Components/DrawComponents/DrawTextComponent.h"

Menu::Menu(Game* game)
        :Scene(game)
//        ,mMenuFont(nullptr)
{
//    mMenuFont = new Font();
//    mMenuFont->Load("../Assets/Fonts/Zelda.ttf");
}

void Menu::Load()
{
    auto *background = new Actor(this);
    // Background and Title
    int width = mGame->GetWindowWidth();
    int height = mGame->GetWindowHeight();

    new DrawSpriteComponent(background, "../Assets/Sprites/Menu/Background.png", width, height);
    new DrawSpriteComponent(background, "../Assets/Sprites/Menu/Title.png", width/2, height/2);

    // Press Space label
    auto *pressSpace = new Actor(this);
    pressSpace->SetPosition(Vector2(mGame->GetWindowWidth()/2.0f, mGame->GetWindowHeight() - 42.0f));
}

void Menu::ProcessInput(const Uint8 *keyState)
{
    if(keyState[SDL_SCANCODE_SPACE])
    {
        mGame->SetScene(Game::GameScene::Overworld);
    }
}