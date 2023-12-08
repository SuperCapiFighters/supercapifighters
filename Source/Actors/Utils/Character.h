//
// Created by julio on 11/11/23.
//

#ifndef SUPER_CAPI_FIGHTERS_CHARACTER_H
#define SUPER_CAPI_FIGHTERS_CHARACTER_H

#include "../../Game.h"

enum class CharacterSelect {
    Goku,
    Vegeta
};

enum class CharacterState {
    Idle,
    Move,
    Jump,
    Down,
    Block,
    JumpBlock,
    DownBlock,
    Punch,
    JumpPunch,
    DownPunch,
    Kick,
    JumpKick,
    DownKick,
    Dead,
    Win,
    Lose,
    BasicDamage,
    BreakBlock
};

class Character {
    public:
        Character();

        const std::vector<int> GetStateArray(CharacterSelect character, CharacterState state);
        const std::string GetCharacterSpriteSheetPath(CharacterSelect character);
        const std::string GetCharacterSpriteSheetJSON(CharacterSelect character);
    private:


};


#endif //SUPER_CAPI_FIGHTERS_CHARACTER_H
