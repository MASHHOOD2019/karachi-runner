cmake_minimum_required(VERSION 3.28)
project(KarachiRunner LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Karachi Runner uses no networking, so the SFML Network module
# is not built at all. Only System, Window, Graphics and Audio.
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(KarachiRunner
    src/main.cpp
    src/Game.cpp
    src/GameState.h
    src/MenuState.cpp
    src/AssetManager.cpp
    src/FileLoadException.cpp
    src/GameObject.cpp
    src/MovingObject.cpp
    src/DrawableObject.cpp
    src/Player.cpp
    src/MashhoodPlayer.cpp
    src/ShayanPlayer.cpp
    src/AryanPlayer.cpp
    src/Obstacle.cpp
    src/Rickshaw.cpp
    src/Pothole.cpp
    src/Barrier.cpp
    src/Bus.cpp
    src/Thela.cpp
    src/Collectible.cpp
    src/Coin.cpp
    src/BiryaniBox.cpp
    src/ChaiCup.cpp
    src/Score.cpp
    src/ScoreMapper.cpp
    src/ScoreManager.cpp
    src/PlayState.cpp
    src/PauseState.cpp
    src/GameOverState.cpp
    src/CreditsState.cpp
    src/Map.cpp
    src/CliftonMap.cpp
    src/ShahrahMap.cpp
    src/UniversityRoadMap.cpp
    src/SaddarMap.cpp
    src/SoundManager.cpp
)

target_compile_features(KarachiRunner PRIVATE cxx_std_17)
target_link_libraries(KarachiRunner PRIVATE SFML::Graphics SFML::Audio)

# Copy the assets folder next to the exe so the game finds its files
add_custom_command(TARGET KarachiRunner POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:KarachiRunner>/assets)
