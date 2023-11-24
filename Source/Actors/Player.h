//
// Created by julio on 10/11/23.
//

#ifndef SUPER_CAPI_FIGHTERS_PLAYER_H
#define SUPER_CAPI_FIGHTERS_PLAYER_H

#pragma once
#include "Actor.h"
#include "Utils/Character.h"

enum class FightStatus {
    Fight,
    Win,
    Lose
};

class Player: public Actor {
public:
    explicit Player(Game* game, Vector2 position, int playerNumber, CharacterSelect characterSelect, float forwardSpeed = 2500.0f, float jumpSpeed = -5000.0f);

    void OnProcessInput(const Uint8* keyState) override;
    void OnUpdate(float deltaTime) override;
    void OnCollision(std::unordered_map<CollisionSide, AABBColliderComponent::Overlap>& responses) override;

    void Kill() override;

private:
    void ManageAnimations();

    class RigidBodyComponent* mRigidBodyComponent;
    class DrawAnimatedComponent* mDrawComponent;
    class AABBColliderComponent* mColliderComponent;
    class DrawPolygonComponent* mDrawPolygonComponent;

    float mForwardSpeed;
    float mJumpSpeed;

    bool mIsMoving;
    bool mIsDead;
    bool mIsOnGround;
    bool mIsJumping;
    bool mIsBlocking;
    bool mIsPunching;
    bool mIsKicking;
    bool mIsDown;


    FightStatus mFightStatus;

    int mPlayerNumber;
    Character* mCharacter;
    CharacterSelect mCharacterSelect;
};


#endif //SUPER_CAPI_FIGHTERS_PLAYER_H
