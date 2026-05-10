#pragma once
#include <SDL3/SDL.h>
#include "Config.h"

namespace LevelEditor {

/**
 * @class Window
 * @brief RAII wrapper around an SDL_Window for the Level Editor.
 *
 * Creates and owns a single SDL window configured with the values
 * from Config::Editor. The window is destroyed automatically when
 * the object goes out of scope.
 *
 * Copy construction and copy assignment are explicitly deleted to
 * prevent accidental double-destruction of the underlying SDL resource.
 */
class Window {
public:
    /**
     * @brief Constructs the editor window using Config::Editor settings.
     *
     * Calls SDL_CreateWindow with the title, width, and height defined
     * in Config::Editor, then checks for SDL errors.
     */
    Window() {
        SDLWindow = SDL_CreateWindow(
            Config::Editor::WINDOW_TITLE.c_str(),
            Config::Editor::WINDOW_WIDTH,
            Config::Editor::WINDOW_HEIGHT,
            0
        );
        CheckSDLError("Creating Editor Window");
    }

    /**
     * @brief Destroys the SDL window if the video subsystem is still active.
     *
     * Guards against calling SDL_DestroyWindow after SDL 
     * has already been shut down.
     */
    ~Window() {
        if (SDLWindow && SDL_WasInit(SDL_INIT_VIDEO)) {
            SDL_DestroyWindow(SDLWindow);
        }
    }

    /// Copying is disabled — the SDL_Window* must have a single owner.
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    /**
     * @brief Clears the window surface to the editor background color.
     *
     * Retrieves the pixel format of the current surface, maps the RGBA
     * background color from Config::Editor, and fills the entire surface.
     * Call Update() afterward to make the result visible.
     */
    void Render() {
        auto [r, g, b, a] {
            Config::Editor::WINDOW_BACKGROUND
        };

        const auto* Fmt = SDL_GetPixelFormatDetails(
            GetSurface()->format
        );

        SDL_FillSurfaceRect(
            GetSurface(), nullptr,
            SDL_MapRGB(Fmt, nullptr, r, g, b)
        );
    }

    /**
     * @brief Pushes the current surface contents to the screen.
     *
     * Wraps SDL_UpdateWindowSurface; must be called after Render()
     * to display the latest frame.
     */
    void Update() {
        SDL_UpdateWindowSurface(SDLWindow);
    }

    /**
     * @brief Returns the drawable surface associated with the window.
     * @return Pointer to the SDL_Surface owned by the window, or nullptr on failure.
     */
    SDL_Surface* GetSurface() const {
        return SDL_GetWindowSurface(SDLWindow);
    }

    /**
     * @brief Checks whether the window currently has mouse focus.
     * @return true if the mouse cursor is inside this window, false otherwise.
     */
    bool HasMouseFocus() const {
        return SDL_GetMouseFocus() == SDLWindow;
    }

    /**
     * @brief Returns the current position of the window on the desktop.
     * @return An SDL_Point containing the (x, y) screen coordinates of the top-left corner.
     */
    SDL_Point GetPosition() const {
        int x, y;
        SDL_GetWindowPosition(SDLWindow, &x, &y);
        return { x, y };
    }
   
    /**
     * @brief Returns the current size of the window.
     * @return An SDL_Point where x is the width and y is the height, in pixels.
     */
    SDL_Point GetSize() const {
        int w, h;
        SDL_GetWindowSize(SDLWindow, &w, &h);
        return { w, h };
    }

    /**
     * @brief Provides direct access to the underlying SDL_Window handle.
     * @return Raw pointer to the SDL_Window; do not store or destroy it externally.
     */
    SDL_Window* GetRaw() const {
        return SDLWindow;
    }

private:
    /// The underlying SDL window handle; owned exclusively by this object.
	SDL_Window* SDLWindow{ nullptr };
};
}