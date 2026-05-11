#include <ranges>
#include "LevelEditor/Level.h"
#include "LevelEditor/Scene.h"

using namespace LevelEditor;

void Level::HandleEvent(const SDL_Event& Event) {
    using namespace std::views;
    for (ActorPtr& A : reverse(Actors)) {
        if (A->HandleEvent(Event)) {
            break;
        }
    }

    if (Event.type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
        Event.button.button == SDL_BUTTON_LEFT) 
    {
        SelectedActor = nullptr;
    }
    else if (Event.type == SDL_EVENT_KEY_DOWN &&
        Event.key.key == SDLK_DELETE && SelectedActor)
    {
        for (size_t i = 0; i < Actors.size(); ++i) {
            if (Actors[i].get() == SelectedActor) {
                Actors.erase(Actors.begin() + i);
                break;
            }
        }

        SelectedActor = nullptr;
    }
}

void Level::Tick(float DeltaTime) {
    for (ActorPtr& A : Actors) {
        A->Tick(DeltaTime);
    }
}

void Level::Render(SDL_Surface* Surface) {
    auto [r, g, b, a] {
      Config::Editor::LEVEL_BACKGROUND
    };

    const auto* Fmt{ SDL_GetPixelFormatDetails(Surface->format) };

    SDL_FillSurfaceRect(
        Surface, &Rect,
        SDL_MapRGB(Fmt, nullptr, r, g, b)
    );

    for (ActorPtr& A : Actors) {
        if (SelectedActor && 
            A.get() == SelectedActor && 
            SelectedActor->GetIsVisible()) 
        {
            auto [x, y, w, h] {SelectedActor->GetRect()};
            SDL_Rect Rect{ x - 1, y - 1, w + 2, h + 2 };
            SDL_FillSurfaceRect(
                Surface, &Rect,
                SDL_MapRGB(Fmt, nullptr, 255, 255, 255)
            );
        }
        A->Render(Surface);
    }
}

/**
 * @brief Function responsible for adding a new actor to the level's collection.
 * @param NewActor The actor to be added on the level.
 *
 * It uses Actors.push_back() to move the actor pointer to the Actors vector.
 * The ownership is transferred to the vector.
 */
void Level::AddToLevel(ActorPtr NewActor) {
    NewActor->SetLocation(ActorLocation::Level);
    Actors.push_back(std::move(NewActor));
}

bool Level::HasMouseFocus() const {
    float MouseX, MouseY;
    SDL_GetMouseState(&MouseX, &MouseY);

    if (
        MouseX <= 0 || MouseY <= 0
        || MouseX >= Config::Editor::LEVEL_WIDTH
        || MouseY >= Config::Editor::LEVEL_HEIGHT
    ) {
        return false;
    }
    return true;
}

void Level::HandleDrop(Actor* DragActor) {
    DragActor->SetIsVisible(true);
    if (!HasMouseFocus()) return;

    float MouseX, MouseY;
    SDL_GetMouseState(&MouseX, &MouseY);
    auto [DragOffsetX, DragOffsetY] = DragActor->GetDragOffset();

    using enum ActorLocation;
    if (DragActor->GetLocation() == Menu) {
        ActorPtr NewActor = DragActor->Clone();
        NewActor->SetPosition(
            int(MouseX) - DragOffsetX,
            int(MouseY) - DragOffsetY
        );
        SelectedActor = NewActor.get();
        AddToLevel(std::move(NewActor));
    }
    else {
        DragActor->SetPosition(
            int(MouseX) - DragOffsetX,
            int(MouseY) - DragOffsetY
        );
        SelectedActor = DragActor;
    }
}