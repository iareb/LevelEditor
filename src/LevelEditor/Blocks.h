#pragma once
#include "Actor.h"

namespace LevelEditor {
class BlueBlock : public Actor {
public:
    static constexpr int WIDTH{ 50 };
    static constexpr int HEIGHT{ 25 };

    BlueBlock(Scene& ParentScene, SDL_Rect Rect);

    Config::ActorType GetActorType() const override {
        return Config::ActorType::BlueBlock;
    }

    std::unique_ptr<Actor> Clone() const override {
        return std::make_unique<BlueBlock>(*this);
    }
};

class GreenBlock : public Actor {
public:
    static constexpr int WIDTH{50};
    static constexpr int HEIGHT{25};

    GreenBlock(Scene& ParentScene, SDL_Rect Rect);

    Config::ActorType GetActorType() const override {
        return Config::ActorType::GreenBlock;
    }

    std::unique_ptr<Actor> Clone() const override {
        return std::make_unique<GreenBlock>(*this);
    }
};
}