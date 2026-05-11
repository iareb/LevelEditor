#pragma once
#include <SDL3/SDL.h>
#include "ActorMenu.h"
#include "AssetManager.h"
#include "Window.h"

namespace LevelEditor {
class Scene {
public:
	Scene(Window& ParentWindow)
	: ParentWindow{ ParentWindow } 
	{}

	void HandleEvent(const SDL_Event& E) {
		ActorShelf.HandleEvent(E);
	}

	void Tick(float DeltaTime) {
		ActorShelf.Tick(DeltaTime);
	}

	void Render(SDL_Surface* Surface) {
		ActorShelf.Render(Surface);
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
	ActorMenu ActorShelf{ *this };
	Window& ParentWindow;
	AssetManager Assets;
};
}