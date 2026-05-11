#pragma once
#include <memory>
#include <SDL3/SDL.h>
#include "Image.h"

enum class ActorLocation { Level, Menu };

namespace LevelEditor {
class Scene;
class Actor {
public:
	Actor(Scene& ParentScene, const SDL_Rect& Rect, Image& Image)
	: ParentScene{ ParentScene }, Rect{ Rect }, Art{ Image }
	{}

	bool HasMouseFocus() const;
	virtual bool HandleEvent(const SDL_Event& E);
	void Tick(float DeltaTime) {}

	void Render(SDL_Surface* Surface) {
		if (GetIsVisible()) {
			Art.Render(Surface, Rect);
		}
	}

	ActorLocation GetLocation() const {
		return Location;
	}

	void SetLocation(ActorLocation NewLocation) {
		Location = NewLocation;
	}


	const SDL_Rect& GetRect() const {
		return Rect;
	}

	const Image& GetArt() const {
		return Art;
	}

	const SDL_Point& GetDragOffset() const {
		return DragOffset;
	}

	SDL_Point GetPosition() const {
		return {Rect.x, Rect.y};
	}

	void SetPosition(int x, int y) {
		Rect.x = x;
		Rect.y = y;
	}

	virtual std::unique_ptr<Actor> Clone() const {
		return std::make_unique<Actor>(*this);
	}

	bool GetIsVisible() const {
		return isVisible;
	}

	void SetIsVisible(bool NewVisibility) {
		isVisible = NewVisibility;
	}

protected:
	ActorLocation Location{ ActorLocation::Menu };
	Scene& ParentScene;
	SDL_Rect Rect;
	Image& Art;
	SDL_Point DragOffset{ 0, 0 };
	bool isVisible{ true };
};
}