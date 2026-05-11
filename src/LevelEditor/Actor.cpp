#include "Actor.h"
#include "Config.h"
#include "Scene.h"

using namespace LevelEditor;

/**
* @brief Function to check if the Actor has mouse focus.
* 
* If the parent scene doesn't have mouse focus, 
* the Actor can't possibly have mouse focus.
* We only consider hover checks when the editor window is active.
* 
* We then fetch mouse coordinates and compare them against 
* the actor's boundaries, defined by Rect.
* If the coordinates lie within the horizontal range (Rect.x to Rect.x + Rect.w)
* and vertical range (Rect.y to Rect.y + Rect.h) the Actor is considered hovered.
*/
bool Actor::HasMouseFocus() const {
	if (!ParentScene.HasMouseFocus()) {
		return false;
	}

	float x, y;
	SDL_GetMouseState(&x, &y);

	if (
		x < Rect.x || x > Rect.x + Rect.w ||
		y < Rect.y || y > Rect.y + Rect.h
		) {
		return false;
	}

	return true;
}

/**
* @brief Function to check for the left mouse button press.
*
*  If an event represents a left-click, it's type will be SDL_EVENT_MOUSE_BUTTON_DOWN, 
*  and the SDL_MouseButtonEvent's button value will be SDL_BUTTON_LEFT. 
*  If both are true, we then also verify HasMouseFocus() to confirm the click 
*  landed within this actor's bounds.
* 
* Upon confirmation, we prepare the event initializing the struct DragEvent.
* To know which actor was clicked, we attach this (pointer to the current actor object)
* to DragEvent.user.data1. This event, carrying the actor pointer, is then injected
* into the event queue via SDL_PushEvent(&DragEvent)
*/
void Actor::HandleEvent(const SDL_Event& E) {
	if (E.type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
		E.button.button == SDL_BUTTON_LEFT &&
		HasMouseFocus()
		) {
		DragOffset.x = int(E.button.x) - Rect.x;
		DragOffset.y = int(E.button.y) - Rect.y;

		SDL_Event DragEvent{ UserEvents::ACTOR_DRAG };
		DragEvent.user.data1 = this;
		SDL_PushEvent(&DragEvent);
	}
}