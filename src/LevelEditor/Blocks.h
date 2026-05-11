#pragma once
#include "Actor.h"

namespace LevelEditor {
class BlueBlock : public Actor {
public:
    static constexpr int WIDTH{ 50 };
    static constexpr int HEIGHT{ 25 };

    BlueBlock(
        Scene& ParentScene, SDL_Rect Rect
    );
};
}