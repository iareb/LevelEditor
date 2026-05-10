#pragma once
#include <SDL3/SDL.h>
#include "AssetManager.h"
#include "Window.h"

namespace LevelEditor {
class Scene {
public:
	Scene(Window& ParentWindow)
	: ParentWindow{ ParentWindow } 
	{}

	void HandleEvent(const SDL_Event& E) {

	}

	void Tick(float DeltaTime) {

	}

	void Render(SDL_Surface* Surface) {

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
	Window& ParentWindow;
	AssetManager Assets;
};
}