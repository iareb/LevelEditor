#pragma once
#include <SDL3/SDL.h>
#include "Image.h"

namespace LevelEditor {
class Scene;
class Actor {
public:
	Actor(Scene& ParentScene, const SDL_Rect& Rect, Image& Image)
	: ParentScene{ ParentScene }, Rect{ Rect }, Art{ Image }
	{}

	virtual void HandleEvent(const SDL_Event& E) {}
	void Tick(float DeltaTime) {}

	void Render(SDL_Surface* Surface) {
		Art.Render(Surface, Rect);
	}

protected:
	Scene& ParentScene;
	SDL_Rect Rect;
	Image& Art;
};
}