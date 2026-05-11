#pragma once
#include <SDL3/SDL.h>
#include "ActorMenu.h"
#include "ActorTooltip.h"
#include "AssetManager.h"
#include "Level.h"
#include "Window.h"

namespace LevelEditor {
class Scene {
public:
	Scene(Window& ParentWindow)
	: ParentWindow{ ParentWindow } 
	{}

	void HandleEvent(const SDL_Event& E) {
		ActorShelf.HandleEvent(E);
		TooltipWindow.HandleEvent(E);
		CurrentLevel.HandleEvent(E);
	}

	void Tick(float DeltaTime) {
		ActorShelf.Tick(DeltaTime);
		TooltipWindow.Tick(DeltaTime);
		CurrentLevel.Tick(DeltaTime);
	}

	void Render(SDL_Surface* Surface) {
		ActorShelf.Render(Surface);
		TooltipWindow.Render();
		CurrentLevel.Render(Surface);
	}

	Level& GetLevel() {
		return CurrentLevel;
	}

	AssetManager& GetAssets() {
		return Assets;
	}

	bool HasMouseFocus() const {
		return ParentWindow.HasMouseFocus();
	}

	Window& GetWindow() const {
		return ParentWindow;
	}

private:
	Level CurrentLevel{ *this };
	ActorMenu ActorShelf{ *this };
	Window& ParentWindow;
	ActorTooltip TooltipWindow{ *this };
	AssetManager Assets;
};
}