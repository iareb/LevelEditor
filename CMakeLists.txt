# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.23)

# Define the project
project(
  LevelEditor
  VERSION 1.0
  DESCRIPTION "Level Editor and game with C++ and SDL3"
  LANGUAGES CXX
)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
list(APPEND CMAKE_PREFIX_PATH "C:/Users/Utente/AppData/Local/bin/NASM")

set(
  CMAKE_RUNTIME_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

set(
  CMAKE_LIBRARY_OUTPUT_DIRECTORY
  "${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

add_executable(LevelEditor
  src/main.cpp
  "src/LevelEditor/Scene.h" "src/LevelEditor/AssetManager.h" "src/LevelEditor/Image.h" "src/LevelEditor/Text.h" "src/LevelEditor/Button.cpp" "src/LevelEditor/ActorMenu.h" "src/LevelEditor/Actor.h" "src/LevelEditor/Blocks.h" "src/LevelEditor/Blocks.cpp" "src/LevelEditor/Actor.cpp" "src/LevelEditor/ActorTooltip.h" "src/LevelEditor/ActorTooltip.cpp"
        src/LevelEditor/Level.h
        src/LevelEditor/Level.cpp
        src/LevelEditor/EditorButtons.h)
 
 target_compile_definitions(
	LevelEditor PUBLIC
	WITH_EDITOR
	CHECK_ERRORS
 )
 
 target_include_directories(
    LevelEditor PUBLIC ${PROJECT_SOURCE_DIR}/src
)

if(APPLE)
  set_target_properties(LevelEditor PROPERTIES
    INSTALL_RPATH "@executable_path;@loader_path"
    BUILD_WITH_INSTALL_RPATH TRUE
    MACOSX_RPATH TRUE
  )
elseif(UNIX)
  set_target_properties(LevelEditor PROPERTIES
    INSTALL_RPATH "$ORIGIN"
    BUILD_WITH_INSTALL_RPATH TRUE
  )
endif()

# Specify that we want to build SDL_TTF's dependencies
set(SDLTTF_VENDORED ON) 

# Set a variable for our vendor directory
set(VENDOR_DIR "${PROJECT_SOURCE_DIR}/vendor") 

# Add the SDL libraries from our submodules
add_subdirectory(${VENDOR_DIR}/SDL) 
add_subdirectory(${VENDOR_DIR}/SDL_image) 
add_subdirectory(${VENDOR_DIR}/SDL_ttf)

target_link_libraries(LevelEditor 
  SDL3::SDL3 
  SDL3_image::SDL3_image 
  SDL3_ttf::SDL3_ttf 
)

set(AssetDirectory "${PROJECT_SOURCE_DIR}/Assets")
add_custom_command(
  TARGET LevelEditor POST_BUILD
  COMMAND
  ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:SDL3::SDL3>"
    "$<TARGET_FILE:SDL3_image::SDL3_image>"
    "$<TARGET_FILE:SDL3_ttf::SDL3_ttf>"
    "$<TARGET_FILE_DIR:LevelEditor>"

  COMMAND
  ${CMAKE_COMMAND} -E copy_directory_if_different
    "${AssetDirectory}"
    "$<TARGET_FILE_DIR:LevelEditor>/Assets"
  VERBATIM
)