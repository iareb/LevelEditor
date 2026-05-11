#include "LevelEditor/Level.h"
#include "LevelEditor/Scene.h"

using namespace LevelEditor;

void Level::HandleEvent(const SDL_Event& Event) {
    for (ActorPtr& A : Actors) {
        A->HandleEvent(Event);
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
    if (!HasMouseFocus()) return;

    float MouseX, MouseY;
    SDL_GetMouseState(&MouseX, &MouseY);
    auto [DragOffsetX, DragOffsetY] = DragActor->GetDragOffset();

    ActorPtr NewActor = DragActor->Clone();
    NewActor->SetPosition(
        int(MouseX) - DragOffsetX,
        int(MouseY) - DragOffsetY
    );
    AddToLevel(std::move(NewActor));
}