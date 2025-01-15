cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME SoundClown)
set(SRC_FILES src/main.cpp src/app.cpp src/window.cpp)
set(COMPILE_DEFINITIONS SDL_MAIN_HANDLED WINDOW_IMP_SDL2)

set(CMAKE_CXX_STANDARD 20)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${COMPILE_DEFINITIONS})

add_subdirectory(SDL)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2-static)