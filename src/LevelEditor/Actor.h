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

	virtual void Serialize(SDL_IOStream* Handle) const {
		using namespace Config::Editor;
		Uint8 ActorType{static_cast<Uint8>(GetActorType())};
		SDL_WriteU8(Handle, ActorType);

		Uint8 GridRow = Rect.y / VERTICAL_GRID_SNAP;
		SDL_WriteU8(Handle, GridRow);
		Uint8 GridColumn = Rect.x / HORIZONTAL_GRID_SNAP;
		SDL_WriteU8(Handle, GridColumn);


	}

	virtual Config::ActorType GetActorType() const {
		return Config::ActorType::Actor;
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