// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include "Actors/Actor.h"
#include "Actors/Player.h"
#include "Components/ColliderComponents/AABBColliderComponent.h"
#include "Components/DrawComponents/DrawComponent.h"
#include "Random.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Scenes/Menu.h"
#include "Scenes/Overworld.h"
#include <algorithm>
#include <fstream>
#include <vector>

Game::Game(int windowWidth, int windowHeight)
    : mWindow(nullptr), mRenderer(nullptr), mTicksCount(0), mIsRunning(true), mUpdatingActors(false), mWindowWidth(windowWidth), mWindowHeight(windowHeight),mGameState(GameScene::Menu) {
}

bool Game::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Super Capi Fighters", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWindowWidth, mWindowHeight, SDL_WINDOW_RESIZABLE);
    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    mAudio = new AudioSystem();

    Random::Init();

    mTicksCount = SDL_GetTicks();

    // Play background music
    mAudio->PlaySound("MusicLoop.ogg", true);

    // Init all game actors
    InitializeActors();

    return true;
}

void Game::InitializeActors() {
    switch (mGameState) {
        case GameScene::Menu:
            mScene = new Menu(this);
            mScene->Load();
            break;

        case GameScene::Overworld:
            mScene = new Overworld(this);
            mScene->Load();
            break;
        default:
            break;
        }
}

void Game::SetScene(GameScene gameState) {
    // Stop all sounds
    mAudio->StopAllSounds();

    // Handle scene transition
    mGameState = gameState;
    UnloadActors();
    InitializeActors();
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            Quit();
            break;
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(nullptr);

    mAudio->ProcessInput(state);
    mScene->ProcessInput(state);

    for (auto actor : mActors) {
        actor->ProcessInput(state);
    }
}

void Game::UpdateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }

    mTicksCount = SDL_GetTicks();

    mAudio->Update(deltaTime);

    // Update all actors and pending actors
    UpdateActors(deltaTime);

    // Update camera position
    UpdateCamera();
}

void Game::UpdateCamera() {
}

void Game::UpdateActors(float deltaTime) {
    mUpdatingActors = true;
    for (auto actor : mActors) {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;

    for (auto pending : mPendingActors) {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    std::vector<Actor *> deadActors;
    for (auto actor : mActors) {
        if (actor->GetState() == ActorState::Destroy) {
            deadActors.emplace_back(actor);
        }
    }

    for (auto actor : deadActors) {
        delete actor;
    }
}

void Game::AddActor(Actor *actor) {
    if (mUpdatingActors) {
        mPendingActors.emplace_back(actor);
    } else {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor *actor) {
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end()) {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }

    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end()) {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Game::AddDrawable(class DrawComponent *drawable) {
    mDrawables.emplace_back(drawable);

    std::sort(mDrawables.begin(), mDrawables.end(), [](DrawComponent *a, DrawComponent *b) {
        return a->GetDrawOrder() < b->GetDrawOrder();
    });
}

void Game::RemoveDrawable(class DrawComponent *drawable) {
    auto iter = std::find(mDrawables.begin(), mDrawables.end(), drawable);
    mDrawables.erase(iter);
}

void Game::AddCollider(class AABBColliderComponent *collider) {
    mColliders.emplace_back(collider);
}

void Game::RemoveCollider(AABBColliderComponent *collider) {
    auto iter = std::find(mColliders.begin(), mColliders.end(), collider);
    mColliders.erase(iter);
}

void Game::GenerateOutput() {
    // Set draw color to black
    SDL_SetRenderDrawColor(mRenderer, 107, 140, 255, 255);

    // Clear back buffer
    SDL_RenderClear(mRenderer);

    for (auto drawable : mDrawables) {
        if (drawable->IsVisible()) {
            drawable->Draw(mRenderer);
        }
    }

    // Swap front buffer and back buffer
    SDL_RenderPresent(mRenderer);
}

void Game::UnloadActors() {
    while (!mActors.empty()) {
        delete mActors.back();
    }

    delete mScene;
}

SDL_Texture *Game::LoadTexture(const std::string &texturePath) {
    SDL_Surface *surface = IMG_Load(texturePath.c_str());
    if (!surface) {
        SDL_Log("Failed to load texture file %s", texturePath.c_str());
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        SDL_Log("Failed to convert surface to texture for %s", texturePath.c_str());
        return nullptr;
    }

    return texture;
}

void Game::Shutdown() {
    while (!mActors.empty()) {
        delete mActors.back();
    }

    delete mAudio;

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}
