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
                    return {10, 11, 12, 13};
                case CharacterState::Move:
                    return {18, 19, 20, 21, 22, 23};
                case CharacterState::Jump:
                    return {33, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40};
                case CharacterState::Down:
                    return {41, 42, 43};
                case CharacterState::Block:
                    return {24, 25, 26};
                case CharacterState::JumpBlock:
                    return {30, 31, 32};
                case CharacterState::DownBlock:
                    return {27, 28, 29};
                case CharacterState::Punch:
                    return {58, 59, 59, 60, 60, 61, 61};
                case CharacterState::JumpPunch:
                    return {88, 89, 90, 91, 92, 93};
                case CharacterState::DownPunch:
                    return {74, 75, 75, 76, 76, 77, 77};
                case CharacterState::Kick:
//                    return {62, 63, 64, 65, 66, 67};
                    return {110, 111, 112, 113, 114, 114, 115};
                case CharacterState::JumpKick:
                    return {84, 85, 86, 87};
                case CharacterState::DownKick:
                    return {78, 79, 80, 81, 82, 83};
                case CharacterState::BasicDamage:
                    return {232, 233, 234, 235, 234, 233, 232};
                case CharacterState::BreakBlock:
                    return {228, 228, 229, 230, 230, 231, 231};
                case CharacterState::Dead:
//                    return {268, 269, 270, 271, 272, 273, 274, 274};
                    return {268, 269, 270};
                case CharacterState::Win:
                    return {275, 276, 277, 278, 279, 280, 281, 282};
                case CharacterState::Lose:
                    return {283, 284, 285, 286};
            }
        case CharacterSelect::Vegeta:
            switch (state) {
                case CharacterState::Idle:
                    return {9, 10, 11, 12};
                case CharacterState::Move:
                    return {17, 18, 19, 20, 21, 22};
                case CharacterState::Jump:
                    return {32, 33, 34, 35, 35, 36, 36, 37, 37, 38, 38};
                case CharacterState::Down:
                    return {39, 40, 41};
                case CharacterState::Block:
                    return {23, 24, 25};
                case CharacterState::JumpBlock:
                    return {29, 30, 31};
                case CharacterState::DownBlock:
                    return {26, 27, 28};
                case CharacterState::Punch:
                    return {59, 60, 60, 61, 61, 62, 62};
                case CharacterState::JumpPunch:
//                    return {89, 90, 91, 92, 93, 94};
                    return {190, 191, 192, 193, 194, 195};
                case CharacterState::DownPunch:
                    return {78, 79, 80, 81, 82, 83, 84};
                case CharacterState::Kick:
                    return {109, 110, 111, 112, 113, 114};
                case CharacterState::JumpKick:
                    return {104, 105, 106, 107, 108};
                case CharacterState::DownKick:
                    return {74, 75, 75, 76, 76, 77, 77};
                case CharacterState::BasicDamage:
                    return {230, 231, 232, 233, 232, 231, 230};
                case CharacterState::BreakBlock:
                    return {218, 219, 219, 220, 220, 221, 221};
                case CharacterState::Dead:
//                    return {258, 259, 260, 261, 262, 263, 264, 265};
                    return {258, 259, 260};
                case CharacterState::Win:
                    return {274, 275, 276, 277, 278, 279, 280, 281, 282};
                case CharacterState::Lose:
//                    return {283, 284, 285, 286, 287, 288};
                    return {283, 284, 285};
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
