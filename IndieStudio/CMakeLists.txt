cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(bomberman)

find_package(raylib 3.0 QUIET) # Let CMake search for a raylib-config.cmake

if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/master.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        # build raylib
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

include_directories(interfaces SRCS)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/ASSETS/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/ASSETS/)

set(Headers
        SRCS/Graphic.hpp
        SRCS/Window.hpp
        SRCS/Core.hpp
        SRCS/Info.hpp
        SRCS/Save.hpp
        SRCS/Sound.hpp
        interfaces/IEntities.hpp
        SRCS/INPUTS/KeyboardInput.hpp
        SRCS/INPUTS/ManetteInput.hpp
        SRCS/CONTROLLERS/Pause.hpp
        SRCS/CONTROLLERS/Input.hpp
        SRCS/CONTROLLERS/Menu.hpp
        SRCS/CONTROLLERS/Game.hpp
        SRCS/CONTROLLERS/Settings.hpp
        SRCS/ENTITIES/Widget.hpp
        SRCS/ENTITIES/Object.hpp
        SRCS/ENTITIES/OBJECTS/Player.hpp
        SRCS/ENTITIES/WIDGETS/Button.hpp
        SRCS/ENTITIES/OBJECTS/Crate.hpp
        SRCS/ENTITIES/OBJECTS/Collide.hpp
        SRCS/ENTITIES/OBJECTS/Serialize.hpp
        SRCS/ENTITIES/OBJECTS/Wall.hpp
        SRCS/ENTITIES/OBJECTS/Bomb.hpp
        SRCS/ENTITIES/OBJECTS/Fire.hpp
        SRCS/ENTITIES/OBJECTS/PowerUp.hpp
        SRCS/ENTITIES/OBJECTS/Floor.hpp
        SRCS/CONTROLLERS/End.hpp
        )

set(Sources
        SRCS/Window.cpp
        SRCS/Graphic.cpp
        SRCS/Core.cpp
        SRCS/Info.cpp
        SRCS/Save.cpp
        SRCS/Sound.cpp
        SRCS/INPUTS/KeyboardInput.cpp
        SRCS/INPUTS/ManetteInput.cpp
        SRCS/CONTROLLERS/Menu.cpp
        SRCS/CONTROLLERS/Pause.cpp
        SRCS/CONTROLLERS/Game.cpp
        SRCS/CONTROLLERS/Input.cpp
        SRCS/CONTROLLERS/Settings.cpp
        SRCS/CONTROLLERS/End.cpp
        SRCS/ENTITIES/Object.cpp
        SRCS/ENTITIES/OBJECTS/Player.cpp
        SRCS/ENTITIES/WIDGETS/Button.cpp
        SRCS/ENTITIES/OBJECTS/Serialize.cpp
        SRCS/ENTITIES/OBJECTS/Crate.cpp
        SRCS/ENTITIES/OBJECTS/Wall.cpp
        SRCS/ENTITIES/OBJECTS/Bomb.cpp
        SRCS/ENTITIES/OBJECTS/Fire.cpp
        SRCS/ENTITIES/OBJECTS/PowerUp.cpp
        SRCS/ENTITIES/WIDGETS/Hud.cpp
        SRCS/ENTITIES/WIDGETS/Text.cpp SRCS/ENTITIES/WIDGETS/Text.hpp)

add_executable(${PROJECT_NAME} main.cpp ${Sources} ${Headers})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
set(CMAKE_CXX_FLAGS -pthread)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()