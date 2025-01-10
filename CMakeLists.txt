cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME SoundClown)
set(SRC_FILES src/main.cpp src/app.cpp src/window.cpp)
set(COMPILE_DEFINITIONS WINDOW_IMP_SDL2)

set(CMAKE_CXX_STANDARD 20)

project(${PROJECT_NAME})
set(VCPKG_TARGET_TRIPLET x64-mingw-static)
include(C:/vcpkg/scripts/buildsystems/vcpkg.cmake)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${COMPILE_DEFINITIONS})

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)