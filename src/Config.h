#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <string>
#include <vector>

namespace Config {
	inline const std::vector BUTTON_COLORS = { 
		  SDL_Color{15, 15, 15, 255},  // Normal
		  SDL_Color{15, 155, 15, 255}, // Hover
		  SDL_Color{225, 15, 15, 255}, // Active
		  SDL_Color{60, 60, 60, 255}   // Disabled
	};

	inline const std::string BASE_PATH{ SDL_GetBasePath() };
	inline const std::string FONT{ BASE_PATH + "Assets/Rubik-SemiBold.ttf" };
	inline constexpr SDL_Color FONT_COLOR{ 255, 255, 255, 255 };
}

#ifdef WITH_EDITOR
namespace Config::Editor {
	inline const std::string WINDOW_TITLE{ "Editor" };
	inline const int WINDOW_WIDTH{ 730 };
	inline const int WINDOW_HEIGHT{ 300 };
	inline const SDL_Color WINDOW_BACKGROUND{ 35, 35, 35, 255 };
}
#endif // WITH_EDITOR

inline void CheckSDLError(const std::string& Msg) {
#ifdef CHECK_ERRORS
	const char* error = SDL_GetError();
	if (*error != '\0') { 
		std::cout << Msg << "Error: " << error << "\n";
		SDL_ClearError();
	}
#endif // CHECK_ERRORS
}