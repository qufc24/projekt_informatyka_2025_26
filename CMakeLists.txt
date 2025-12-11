# Minimalna wymagana wersja CMake
cmake_minimum_required(VERSION 3.10)

# Nazwa projektu
project(Arkanoid)

# Ustawienie standardu C++ na C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Wymagana biblioteka SFML. Potrzebna biblioteka: graphics, window, system, audio.
find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

include_directories(gamefiles)
file(GLOB_RECURSE SOURCES "gamefiles/*.cpp")
add_executable(arkanoid ${SOURCES})

target_link_libraries(arkanoid PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)

set(RESOURCE_DIRS data fonts textures sounds)

foreach(DIR ${RESOURCE_DIRS})
    add_custom_command(
        TARGET arkanoid POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/${DIR}"
        "$<TARGET_FILE_DIR:arkanoid>/${DIR}"
        COMMENT "Copying resource directory: ${DIR}"
    )
endforeach()
