#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <string>
#include <vector>

/**
 * @namespace Config
 * @brief Application-wide global configuration constants.
 *
 * Holds shared constants for button colors, asset paths, and other
 * settings used throughout the SDL rendering pipeline.
 */
namespace Config {

	/**
	 * @brief Color palette for the different states of a button.
	 */
	inline const std::vector BUTTON_COLORS = { 
		  SDL_Color{15, 15, 15, 255},  // Normal
		  SDL_Color{15, 155, 15, 255}, // Hover
		  SDL_Color{225, 15, 15, 255}, // Active
		  SDL_Color{60, 60, 60, 255}   // Disabled
	};

	/// Absolute base path of the executable, as returned by SDL_GetBasePath().
	inline const std::string BASE_PATH{ SDL_GetBasePath() };

	/// Absolute path to the application's primary font file.
	inline const std::string FONT{ BASE_PATH + "Assets/Rubik-SemiBold.ttf" };

	/// Default text color (opaque white).
	inline constexpr SDL_Color FONT_COLOR{ 255, 255, 255, 255 };
}

#ifdef WITH_EDITOR
/**
 * @namespace Config::Editor
 * @brief Editor window configuration (only compiled with WITH_EDITOR).
 *
 * Keeps editor-specific settings isolated from the main runtime
 * configuration so they are stripped out in non-editor builds.
 */
namespace Config::Editor {
	/**
	 * @brief Configuration for the level area.
	 */
	inline const int HORIZONTAL_GRID_SNAP{ 50 };
	inline const int VERTICAL_GRID_SNAP{ 25 };
	inline const Uint8 GRID_WIDTH{ 13 };
	inline const Uint8 GRID_HEIGHT{ 6 };
	inline const int LEVEL_WIDTH{ HORIZONTAL_GRID_SNAP * GRID_WIDTH };
	inline const int LEVEL_HEIGHT{ VERTICAL_GRID_SNAP * GRID_HEIGHT };
	inline constexpr SDL_Color LEVEL_BACKGROUND{ 50, 50, 50, 255 };

	/**
	 * @brief Configuration for the editor Window.
	 */
	inline const int ACTOR_MENU_WIDTH{ 70 };
	inline const std::string WINDOW_TITLE{ "Editor" };
	inline const int WINDOW_WIDTH{ LEVEL_WIDTH + ACTOR_MENU_WIDTH };
	inline const int WINDOW_HEIGHT{ LEVEL_HEIGHT + 50 };
	inline const SDL_Color WINDOW_BACKGROUND{ 35, 35, 35, 255 };

	/**
	 * @brief Configuration for the Actor menu.
	 */
	inline const int ACTOR_MENU_POSITION_X{ LEVEL_WIDTH };
	inline const SDL_Color ACTOR_MENU_BACKGROUND{ 15, 15, 15, 255 };
	inline const int PADDING{ 10 };
}
#endif

namespace UserEvents {
#ifdef WITH_EDITOR
	inline Uint32 ACTOR_DRAG{ SDL_RegisterEvents(1) };
#endif 

}

/**
 * @brief Checks for a pending SDL error and prints it if one is found.
 *
 * Compiled only when CHECK_ERRORS is defined; otherwise the call is
 * a no-op with zero runtime overhead.
 *
 * @param Msg A descriptive prefix printed before the SDL error string,
 *            useful for pinpointing where in the code the error occurred.
 */
inline void CheckSDLError(const std::string& Msg) {
#ifdef CHECK_ERRORS
	const char* error = SDL_GetError();
	if (*error != '\0') { 
		std::cout << Msg << "Error: " << error << "\n";
		SDL_ClearError();
	}
#endif // CHECK_ERRORS
}