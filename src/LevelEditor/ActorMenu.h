#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include "Actor.h"
#include "Config.h"
#include "Blocks.h"

namespace LevelEditor {
class Scene;
using ActorPtr = std::unique_ptr<Actor>;
using ActorPtrs = std::vector<ActorPtr>;

class ActorMenu {
public:
    ActorMenu(Scene& ParentScene)
        : ParentScene{ ParentScene }
    {
        using namespace Config::Editor;
        Actors.emplace_back(
            std::make_unique<BlueBlock>(
                GetScene(),
                SDL_Rect{
                    ACTOR_MENU_POSITION_X + PADDING,
                    PADDING,
                    0, 0
                }
            )
        );
    }

    void HandleEvent(const SDL_Event& E) {
        for (ActorPtr& A : Actors) {
            A->HandleEvent(E);
        }
    }
    
    void Tick(float DeltaTime) {
        for (ActorPtr& A : Actors) {
            A->Tick(DeltaTime);
        }
    }
    
    void Render(SDL_Surface* Surface) {
        using namespace Config::Editor;
        auto [r, g, b, a] { ACTOR_MENU_BACKGROUND};

        const auto* Fmt{ SDL_GetPixelFormatDetails(Surface->format) };

        SDL_FillSurfaceRect(
            Surface, &Rect,
            SDL_MapRGB(Fmt, nullptr, r, g, b)
        );

        for (ActorPtr& A : Actors) {
            A->Render(Surface);
        }
    }

    Scene& GetScene() const {
        return ParentScene;
    }

private:
    ActorPtrs Actors;
    Scene& ParentScene;
    SDL_Rect Rect{ 
        Config::Editor::ACTOR_MENU_POSITION_X, 0,
        Config::Editor::ACTOR_MENU_WIDTH,
        Config::Editor::WINDOW_HEIGHT
    };
};
}