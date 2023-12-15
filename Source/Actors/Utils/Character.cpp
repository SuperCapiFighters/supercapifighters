//
// Created by julio on 11/11/23.
//

#include "Character.h"

Character::Character() {

}

const std::vector<int> Character::GetStateArray(CharacterSelect character, CharacterState state) {
    switch (character) {
        case CharacterSelect::Goku:
            switch (state) {
                case CharacterState::Idle:
                    return {10, 11, 12, 13, 12, 11, 10, 11, 12, 13, 12, 11};
                case CharacterState::Move:
                    return {18, 19, 20, 21, 22, 23, 22, 21, 20, 19, 18, 19};
                case CharacterState::Jump:
                    return {33, 34, 35, 36, 37, 38, 39, 40};
                case CharacterState::Down:
                    return {41, 41, 42, 42, 43, 43};
                case CharacterState::Block:
                    return {24, 24, 25, 25, 26, 26};
                case CharacterState::JumpBlock:
                    return {30, 30, 31, 31, 32, 32};
                case CharacterState::DownBlock:
                    return {27, 27, 28, 28, 29, 29};
                case CharacterState::Punch:
                    return {58, 59, 60, 61, 61, 60, 59, 58};
                case CharacterState::JumpPunch:
                    return {88, 89, 90, 91, 92, 93};
                case CharacterState::DownPunch:
                    return {74, 75, 76, 77, 77, 76, 75, 74};
                case CharacterState::Kick:
                    return {110, 111, 112, 113, 114, 115};
                case CharacterState::JumpKick:
                    return {104, 104, 105, 105, 106, 106, 107, 107, 108, 109};
                case CharacterState::DownKick:
                    return {78, 79, 80, 81, 82, 83};
                case CharacterState::BasicDamage:
                    return {232, 233, 234, 235, 235, 234, 233, 232};
                case CharacterState::BreakBlock:
                    return {228, 228, 229, 229, 230, 230, 231, 231};
                case CharacterState::Dead:
                    return {268, 269, 269, 270};
                case CharacterState::Win:
                    return {275, 276, 277, 277, 278, 278, 279, 279, 280, 281, 282, 282};
                case CharacterState::Lose:
                    return {283, 284, 285, 286};
            }
        case CharacterSelect::Vegeta:
            switch (state) {
                case CharacterState::Idle:
                    return {9, 10, 11, 12, 11, 10, 9, 10, 11, 12, 11, 10};
                case CharacterState::Move:
                    return {17, 18, 19, 20, 21, 22, 21, 20, 19, 18, 17, 18};
                case CharacterState::Jump:
                    return {32, 33, 34, 35, 36, 36, 37, 38};
                case CharacterState::Down:
                    return {39, 39, 40, 40, 41, 41};
                case CharacterState::Block:
                    return {23, 23, 24, 24, 25, 25};
                case CharacterState::JumpBlock:
                    return {29, 29, 30, 30, 31, 31};
                case CharacterState::DownBlock:
                    return {26, 26, 27, 27, 28, 28};
                case CharacterState::Punch:
                    return {59, 60, 61, 62, 62, 61, 60, 59};
                case CharacterState::JumpPunch:
                    return {190, 191, 192, 193, 194, 195};
                case CharacterState::DownPunch:
                    return {78, 79, 80, 81, 81, 82, 83, 84, 83};
                case CharacterState::Kick:
                    return {109, 110, 111, 112, 113, 114};
                case CharacterState::JumpKick:
                    return {104, 104, 105, 105, 106, 106, 107, 107, 108, 108};
                case CharacterState::DownKick:
                    return {74, 75, 76, 77, 76, 75};
                case CharacterState::BasicDamage:
                    return {230, 231, 232, 233, 233, 232, 231, 230};
                case CharacterState::BreakBlock:
                    return {218, 218, 219, 219, 220, 220, 221, 221};
                case CharacterState::Dead:
                    return {258, 259, 259, 260};
                case CharacterState::Win:
                    return {274, 275, 276, 277, 278, 279, 280, 280, 281, 281, 282, 282};
                case CharacterState::Lose:
//                    return {283, 284, 285, 286, 287, 288};
                    return {283, 284, 285, 285};
            }
    }
}

const std::string Character::GetCharacterSpriteSheetPath(CharacterSelect character) {
    switch (character) {
        case CharacterSelect::Goku:
            return "../Assets/Sprites/Goku/Goku.png";
        case CharacterSelect::Vegeta:
            return "../Assets/Sprites/Vegeta/Vegeta.png";
    }
}

const std::string Character::GetCharacterSpriteSheetJSON(CharacterSelect character) {
    switch (character) {
        case CharacterSelect::Goku:
            return "../Assets/Sprites/Goku/Goku.json";
        case CharacterSelect::Vegeta:
            return "../Assets/Sprites/Vegeta/Vegeta.json";
    }
}
