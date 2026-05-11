#include "ActorTooltip.h"
#include "Scene.h"

using namespace LevelEditor;

ActorTooltip::ActorTooltip(Scene& ParentScene)
  : ParentScene{ParentScene} {
  SDLWindow = SDL_CreatePopupWindow(
    ParentScene.GetWindow().GetRaw(),
    0, 0, 100, 100,
    SDL_WINDOW_HIDDEN
    | SDL_WINDOW_TOOLTIP
    | SDL_WINDOW_BORDERLESS
    | SDL_WINDOW_ALWAYS_ON_TOP
    | SDL_WINDOW_NOT_FOCUSABLE
  );
  CheckSDLError("Creating Tooltip Window");
}

ActorTooltip::~ActorTooltip() {
  if (!SDL_WasInit(SDL_INIT_VIDEO)) return;
  if (SDLWindow) {
    SDL_DestroyWindow(SDLWindow);
  }
}

void ActorTooltip::PositionWindow() {
  float x, y;
  SDL_GetMouseState(&x, &y);

  auto [DragOffsetX, DragOffsetY] {
    DragActor->GetDragOffset()
  };

  SDL_SetWindowPosition(
    SDLWindow,
    int(x) - DragOffsetX,
    int(y) - DragOffsetY
  );
}

void ActorTooltip::SetIsVisible(bool NewVisibility) {
  isVisible = NewVisibility;
  if (isVisible) {
    SDL_ShowWindow(SDLWindow);
  } else {
    SDL_HideWindow(SDLWindow);
  }
}

void ActorTooltip::HandleEvent(const SDL_Event& E) {
  using namespace UserEvents;
  if (E.type == ACTOR_DRAG) {
    SetIsVisible(true);
    DragActor = static_cast<Actor*>(E.user.data1);
    SDL_SetWindowSize(
      SDLWindow,
      DragActor->GetRect().w,
      DragActor->GetRect().h
    );
  }
}

void ActorTooltip::Tick(float DeltaTime) {
  if (!isVisible) return;

  auto Buttons{ SDL_GetMouseState(nullptr, nullptr) };
  if (!(Buttons & SDL_BUTTON_MASK(SDL_BUTTON_LEFT))) {
    SetIsVisible(false);
  } else {
    PositionWindow();
  }
}

void ActorTooltip::Render() {
  if (!isVisible) return;
  DragActor->GetArt().Render(
    GetSurface(),
    SDL_Rect{
      0, 0,
      DragActor->GetRect().w,
      DragActor->GetRect().h
    }
  );
  SDL_UpdateWindowSurface(SDLWindow);
}
