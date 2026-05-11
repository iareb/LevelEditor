#include "Blocks.h"
#include "Scene.h"

using namespace LevelEditor;

BlueBlock::BlueBlock(Scene& ParentScene, SDL_Rect Rect)
	: Actor{
		ParentScene,
		SDL_Rect{Rect.x, Rect.y, WIDTH, HEIGHT},
		ParentScene.GetAssets().BlueBlock
	}
{}