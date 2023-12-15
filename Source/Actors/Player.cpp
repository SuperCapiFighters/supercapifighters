//
// Created by julio on 10/11/23.
//

#include "Player.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"
#include "../Components/DrawComponents/DrawHealthBar.h"

#define FLOOR_HEIGHT 50.0f

Player::Player(Scene *scene, Vector2 position, int playerNumber, CharacterSelect characterSelect,float heart, float forwardSpeed, float jumpSpeed)
        : Actor(scene, heart, position),
          mPlayerNumber(playerNumber),
          mCharacterSelect(characterSelect),
          mForwardSpeed(forwardSpeed),
          mJumpSpeed(jumpSpeed),
          mIsDead(false),
          mIsOnGround(true),
          mIsJumping(false),
          mIsDown(false),
          mIsBlocking(false),
          mIsPunching(false),
          mIsKicking(false),
          mIsMoving(false),
          mIsDamage(false),
          mAnimationTimer(0.0f),
//          mHeart(heart),
//          mMaxHeart(heart),
          mFightStatus(FightStatus::Fight) {

    mRigidBodyComponent = new RigidBodyComponent(this, 1.25f, 2.0f);
    const float width = 200.0f;
    const float height = 320.0f;

//    mDrawPolygonComponent = new DrawPolygonComponent(this,0,0, width, height);

    if(mPlayerNumber == 2){
        mMovementColliderComponent = new AABBColliderComponent(this, 0, 0, width, height, ColliderLayer::Player2);
        // mPunchColliderComponent = new AABBColliderComponent(this,-65,55,-200,50,ColliderLayer::Punch);
        mDrawPunchComponent = new DrawPolygonComponent(this,-205,55,-50,50);
        mDrawHealthBar = new DrawHealthBar(this,true,10+ mScene->GetGame()->GetWindowWidth()/2,10, mScene->GetGame()->GetWindowWidth()/2-20,20);
    }else{
        mMovementColliderComponent = new AABBColliderComponent(this, 0, 0, width, height, ColliderLayer::Player1);
        // mPunchColliderComponent = new AABBColliderComponent(this,200,55,200,50,ColliderLayer::Punch);
        mDrawPunchComponent = new DrawPolygonComponent(this,205,55,50,50);
        mDrawHealthBar = new DrawHealthBar(this,false,10,10, mScene->GetGame()->GetWindowWidth()/2-20,20);
    }

    // mPunchColliderComponent->SetEnabled(false);
//    mDrawPunchComponent->setIsDraw(false);

    mRotation = mPlayerNumber == 1 ? Math::Pi : 0.0f;

    mCharacter = new Character();

    mDrawComponent = new DrawAnimatedComponent(this, mCharacter->GetCharacterSpriteSheetPath(mCharacterSelect), mCharacter->GetCharacterSpriteSheetJSON(mCharacterSelect));

    mDrawComponent->AddAnimation("idle", mCharacter->GetStateArray(mCharacterSelect, CharacterState::Idle));
    mDrawComponent->AddAnimation("block", mCharacter->GetStateArray(mCharacterSelect, CharacterState::Block), false);
    mDrawComponent->AddAnimation("jump_block", mCharacter->GetStateArray(mCharacterSelect, CharacterState::JumpBlock), false);
    mDrawComponent->AddAnimation("down_block", mCharacter->GetStateArray(mCharacterSelect, CharacterState::DownBlock), false);
    mDrawComponent->AddAnimation("dead", mCharacter->GetStateArray(mCharacterSelect, CharacterState::Dead), false);
    mDrawComponent->AddAnimation("win", mCharacter->GetStateArray(mCharacterSelect, CharacterState::Win), false);
    mDrawComponent->AddAnimation("lose", mCharacter->GetStateArray(mCharacterSelect, CharacterState::Lose), false);
    mDrawComponent->AddAnimation("down", mCharacter->GetStateArray(mCharacterSelect, CharacterState::Down), false);
    mDrawComponent->AddAnimation("jump", mCharacter->GetStateArray(mCharacterSelect, CharacterState::Jump), true);
    mDrawComponent->SetAnimFPS(8.0f);

    mDrawComponent->AddAnimation("move", mCharacter->GetStateArray(mCharacterSelect, CharacterState::Move));
    mDrawComponent->SetAnimFPS(18.0f, "move");

    mDrawComponent->AddAnimation("basic_damage", mCharacter->GetStateArray(mCharacterSelect, CharacterState::BasicDamage), true);
    mDrawComponent->SetAnimFPS(12.0f, "basic_damage");

    mDrawComponent->AddAnimation("break_block", mCharacter->GetStateArray(mCharacterSelect, CharacterState::BreakBlock), true);
    mDrawComponent->SetAnimFPS(10.0f, "break_block");

    mDrawComponent->AddAnimation("punch", mCharacter->GetStateArray(mCharacterSelect, CharacterState::Punch), true);
    mDrawComponent->SetAnimFPS(12.0f, "punch");

    mDrawComponent->AddAnimation("down_punch", mCharacter->GetStateArray(mCharacterSelect, CharacterState::DownPunch), true);
    mDrawComponent->SetAnimFPS(12.0f, "down_punch");

    mDrawComponent->AddAnimation("jump_punch", mCharacter->GetStateArray(mCharacterSelect, CharacterState::JumpPunch), true);
    mDrawComponent->SetAnimFPS(14.0f, "jump_punch");

    mDrawComponent->AddAnimation("kick", mCharacter->GetStateArray(mCharacterSelect, CharacterState::Kick), true);
    mDrawComponent->SetAnimFPS(9.0f, "kick");

    mDrawComponent->AddAnimation("down_kick", mCharacter->GetStateArray(mCharacterSelect, CharacterState::DownKick), true);
    mDrawComponent->SetAnimFPS(9.0f, "down_kick");

    mDrawComponent->AddAnimation("jump_kick", mCharacter->GetStateArray(mCharacterSelect, CharacterState::JumpKick), true);
    mDrawComponent->SetAnimFPS(9.0f, "jump_kick");


}

void Player::OnProcessInput(const uint8_t *state) {
        if(mIsDead || mFightStatus != FightStatus::Fight)
            return;

        if(mIsDamage)
            return;


        if(!mIsDown){
            if (mPlayerNumber == 1 && state[SDL_SCANCODE_D] || mPlayerNumber == 2 && state[SDL_SCANCODE_RIGHT]) {
                mRigidBodyComponent->ApplyForce(Vector2(mForwardSpeed, 0.0f));
                mIsMoving = true;
            }

            if (mPlayerNumber == 1 && state[SDL_SCANCODE_A] || mPlayerNumber == 2 && state[SDL_SCANCODE_LEFT]) {
                mRigidBodyComponent->ApplyForce(Vector2(-mForwardSpeed, 0.0f));
                mIsMoving = true;
            }
        }


        if (mPlayerNumber == 1 && !state[SDL_SCANCODE_D] && !state[SDL_SCANCODE_A] || mPlayerNumber == 2 && !state[SDL_SCANCODE_RIGHT] && !state[SDL_SCANCODE_LEFT]) {
            mIsMoving = false;
        }

        if (!mIsJumping && (mPlayerNumber == 1 && state[SDL_SCANCODE_W] || mPlayerNumber == 2 && state[SDL_SCANCODE_UP])) {
            if(mIsOnGround){
                mRigidBodyComponent->SetVelocity(Vector2(mRigidBodyComponent->GetVelocity().x, mJumpSpeed));
                mIsOnGround = false;
                mIsJumping = true;
                mScene->GetGame()->GetAudio()->PlaySound(mPlayerNumber == 1 ? "GokuJump.wav" : "VegetaJump.wav");
            }
        }

        if(!mIsPunching && (mPlayerNumber == 1 && state[SDL_SCANCODE_R] || mPlayerNumber == 2 && state[SDL_SCANCODE_KP_2])) {
            mIsPunching = true;
            mIsBlocking = false;
            mIsKicking = false;
            mScene->GetGame()->GetAudio()->PlaySound(mPlayerNumber == 1 ? "GokuAttack.wav" : "VegetaAttack.wav");
        } else if(!mIsKicking && (mPlayerNumber == 1 && state[SDL_SCANCODE_T] || mPlayerNumber == 2 && state[SDL_SCANCODE_KP_3])) {
            mIsKicking = true;
            mIsBlocking = false;
            mIsPunching = false;
            mScene->GetGame()->GetAudio()->PlaySound(mPlayerNumber == 1 ? "GokuAttack.wav" : "VegetaAttack.wav");
        } else if(mPlayerNumber == 1 && state[SDL_SCANCODE_E] || mPlayerNumber == 2 && state[SDL_SCANCODE_KP_1]) {
            mIsBlocking = true;
            mIsPunching = false;
            mIsKicking = false;
        } else {
            mIsBlocking = false;
        }

        if(mPlayerNumber == 1 && state[SDL_SCANCODE_S] || mPlayerNumber == 2 && state[SDL_SCANCODE_DOWN]) {
            mIsDown = true;
        } else {
            mIsDown = false;
        }
}

void Player::OnUpdate(float deltaTime) {
    if (mIsPunching) {
        mPunchColliderComponent->SetEnabled(true);
//        mDrawPunchComponent->setIsDraw(true);
            this->StopAnimationTimer(deltaTime, 0.45f, "punch");
    } else if (mIsKicking) {
        mPunchColliderComponent->SetEnabled(true);
//        mDrawPunchComponent->setIsDraw(true);
        this->StopAnimationTimer(deltaTime, 0.40f, "kick");
    } else if (mIsDamage) {
        this->StopAnimationTimer(deltaTime, 0.80f, "damage");
        mAnimationTimer += deltaTime;
    } else if (mIsDead) {
        mAnimationTimer += deltaTime;
        if (mAnimationTimer >= 1.5f) {
            mScene->EndFight();
        }
    } else {
        mPunchColliderComponent->SetEnabled(false);
//        mDrawPunchComponent->setIsDraw(false);
    }


    if (mRigidBodyComponent->GetOwner()->GetPosition().x - mMovementColliderComponent->GetWidth() /2 < mScene->GetGame()->GetCameraPos().x)
        mRigidBodyComponent->GetOwner()->SetPosition(Vector2(mScene->GetGame()->GetCameraPos().x + mMovementColliderComponent->GetWidth() /2, mRigidBodyComponent->GetOwner()->GetPosition().y));

    if (mRigidBodyComponent->GetOwner()->GetPosition().x + mMovementColliderComponent->GetWidth()/2 > mScene->GetGame()->GetWindowWidth())
        mRigidBodyComponent->GetOwner()->SetPosition(Vector2(mScene->GetGame()->GetWindowWidth() - mMovementColliderComponent->GetWidth()/2, mRigidBodyComponent->GetOwner()->GetPosition().y));

    if (mRigidBodyComponent->GetOwner()->GetPosition().y + mMovementColliderComponent->GetHeight()/2 > mScene->GetGame()->GetWindowHeight() - FLOOR_HEIGHT){
        mRigidBodyComponent->GetOwner()->SetPosition(Vector2(mRigidBodyComponent->GetOwner()->GetPosition().x, mScene->GetGame()->GetWindowHeight() - mMovementColliderComponent->GetHeight()/2 - FLOOR_HEIGHT));
        mIsOnGround = true;
        mIsJumping = false;
    }

    ManageAnimations();
}

void Player::StopAnimationTimer(float deltaTime, float animationTime, std::string variable) {
    mAnimationTimer += deltaTime;
    if (mAnimationTimer >= animationTime) {
        mAnimationTimer = 0.0f;
        if(variable == "punch") mIsPunching = false;
        if(variable == "kick") mIsKicking = false;
        if(variable == "damage") mIsDamage = false;
    }
}

void Player::ManageAnimations() {
    if(mFightStatus == FightStatus::Fight) {
        if(mIsDead) {
            mDrawComponent->SetAnimation("dead");
        } else {
            if(mIsOnGround) {
                if(mIsDamage) {
                    if(mIsBlocking){
                        mDrawComponent->SetAnimation("break_block");
                    } else {
                        mDrawComponent->SetAnimation("basic_damage");
                    }
                } else if(mIsDown) {
                    if(mIsBlocking){
                        mDrawComponent->SetAnimation("down_block");
                    } else if (mIsPunching){
                        mDrawComponent->SetAnimation("down_punch");
                    } else if (mIsKicking){
                        mDrawComponent->SetAnimation("down_kick");
                    } else {
                        mDrawComponent->SetAnimation("down");
                    }
                } else if (mIsBlocking) {
                    mDrawComponent->SetAnimation("block");
                } else if (mIsPunching){
                    mDrawComponent->SetAnimation("punch");
                } else if (mIsKicking){
                    mDrawComponent->SetAnimation("kick");
                } else if(mIsMoving) {
                    mDrawComponent->SetAnimation("move");
                } else  {
                    mDrawComponent->SetAnimation("idle");
                }
            } else if (mIsJumping) {
                if (mIsBlocking) {
                    mDrawComponent->SetAnimation("jump_block");
                } else if (mIsPunching) {
                    mDrawComponent->SetAnimation("jump_punch");
                } else if (mIsKicking) {
                    mDrawComponent->SetAnimation("jump_kick");
                } else {
                    mDrawComponent->SetAnimation("jump");
                }
            }
        }
    } else if(mFightStatus == FightStatus::Win) {
        mDrawComponent->SetAnimation("win");
    } else if(mFightStatus == FightStatus::Lose) {
        mDrawComponent->SetAnimation("lose");
    }
}

void Player::Kill() {
    mDrawComponent->SetAnimation("dead");
    mIsDead = true;
    ColliderLayer colliderLayer = mPlayerNumber == 1 ? ColliderLayer::Player1 : ColliderLayer::Player2;
    mMovementColliderComponent = new AABBColliderComponent(this, 0, 0, 200.0f, 50.0f, colliderLayer);
    mMovementColliderComponent->SetEnabled(false);
}

void Player::EndFight() {
    if(mFightStatus == FightStatus::Fight) {
        mFightStatus = mHeart <= 0.0f ? FightStatus::Lose : FightStatus::Win;

        if(mFightStatus == FightStatus::Win){
            if(mPlayerNumber == 1){
                mScene->GetGame()->GetAudio()->PlaySound("GokuWin.wav");
            } else if(mPlayerNumber == 2){
                mScene->GetGame()->GetAudio()->PlaySound("VegetaWin.wav");
            }
        }

        ColliderLayer layer = mPlayerNumber == 1 ? ColliderLayer::Player1 : ColliderLayer::Player2;
        mMovementColliderComponent = new AABBColliderComponent(this, 0, 0, 200.0f, 400.0f, layer);
        mMovementColliderComponent->SetEnabled(false);

        Vector2 position = mPlayerNumber == 1 ? Vector2(300.0f,mScene->GetGame()->GetWindowHeight() - 600.0f) : Vector2(mScene->GetGame()->GetWindowWidth() - 300.0f,mScene->GetGame()->GetWindowHeight() - 600.0f);
        this->SetPosition(position);
    }
}

void Player::OnCollision(std::unordered_map<CollisionSide, AABBColliderComponent::Overlap> &responses) {
    if(mPunchColliderComponent->IsEnabled())
        for (auto &response : responses) {
            if((mPlayerNumber == 1 && response.second.target->GetLayer() == ColliderLayer::Player2)
                || (mPlayerNumber == 2 && response.second.target->GetLayer() == ColliderLayer::Player1)
            ){
                response.second.target->GetOwner()->ApplyDamage(10.0);
                Vector2 playerPosition = response.second.target->GetOwner()->GetPosition();
                Vector2 myPosition = GetPosition();
                Vector2 offsetAttack = Vector2(20,5);
                if(mPlayerNumber==1){
                    response.second.target->GetOwner()->SetPosition(playerPosition+offsetAttack);
                    SetPosition(myPosition-offsetAttack);
                }else{
                    response.second.target->GetOwner()->SetPosition(playerPosition-offsetAttack);
                    SetPosition(myPosition+offsetAttack);
                }
            }
    }

    for(auto &response: responses){
        if(response.second.target->GetLayer() == ColliderLayer::Punch && (mPlayerNumber == 2 && response.second.target->GetLayer() == ColliderLayer::Player2)
           || (mPlayerNumber == 1 && response.second.target->GetLayer() == ColliderLayer::Player1)
           ){
//            response.second.target->GetOwner().
//            printf("-2\n");
//            printf("%d\n", response.second.target->GetOwner()->GetComponent<Player>()->GetPlayerNumber());
//            ApplyDamage(10);
        }
    }
}

void Player::ApplyDamage(float damage) {
    mIsDamage = true;
//    printf("%f\n",mHeart);

    if(mIsBlocking) {
        mHeart -= damage/(float)2.0;
    } else {
        mHeart -= damage;
    }
//    printf("%f\n",mHeart);

    if(mHeart == 0.0){
        mIsDead = true;
        Kill();
    }

}