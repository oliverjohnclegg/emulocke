cmake_minimum_required(VERSION 3.25)
project(emulocke LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

include(FetchContent)

find_package(SDL3 QUIET CONFIG)
if(NOT SDL3_FOUND)
    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.22
        GIT_SHALLOW TRUE)
    set(SDL_SHARED OFF CACHE BOOL "" FORCE)
    set(SDL_STATIC ON CACHE BOOL "" FORCE)
    set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
    set(SDL_TESTS OFF CACHE BOOL "" FORCE)
    set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(SDL3)
endif()

set(BUILD_QT_SDL OFF CACHE BOOL "" FORCE)
set(ENABLE_OGLRENDERER OFF CACHE BOOL "" FORCE)
set(ENABLE_GDBSTUB OFF CACHE BOOL "" FORCE)
set(ENABLE_LTO_RELEASE OFF CACHE BOOL "" FORCE)
set(ENABLE_LTO OFF CACHE BOOL "" FORCE)
set(USE_VCPKG OFF CACHE BOOL "" FORCE)
if(MSVC)
    set(ENABLE_JIT OFF CACHE BOOL "" FORCE)
endif()
if(WIN32 AND NOT MINGW)
    FetchContent_Declare(
        dirent
        GIT_REPOSITORY https://github.com/tronkko/dirent.git
        GIT_TAG 1.26
        GIT_SHALLOW TRUE)
    set(DIRENT_EXAMPLES OFF CACHE STRING "" FORCE)
    set(DIRENT_TESTS OFF CACHE STRING "" FORCE)
    FetchContent_MakeAvailable(dirent)
    set(DIRENT_INCLUDE_DIRS "${dirent_SOURCE_DIR}/include" CACHE PATH "" FORCE)
endif()
set(BUILD_STATIC OFF CACHE BOOL "" FORCE)
add_subdirectory(third_party/melonDS EXCLUDE_FROM_ALL)

set(LIBMGBA_ONLY ON)
set(M_CORE_GB OFF)
set(BUILD_QT OFF CACHE BOOL "" FORCE)
set(BUILD_SDL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(BUILD_STATIC ON CACHE BOOL "" FORCE)
add_subdirectory(third_party/mgba EXCLUDE_FROM_ALL)

add_library(imgui STATIC
    third_party/imgui/imgui.cpp
    third_party/imgui/imgui_draw.cpp
    third_party/imgui/imgui_tables.cpp
    third_party/imgui/imgui_widgets.cpp
    third_party/imgui/backends/imgui_impl_sdl3.cpp
    third_party/imgui/backends/imgui_impl_sdlrenderer3.cpp)
target_include_directories(imgui PUBLIC
    third_party/imgui
    third_party/imgui/backends)
target_link_libraries(imgui PUBLIC SDL3::SDL3)

add_executable(emulocke
    src/main.cpp
    src/application/Host.cpp
    src/application/Application.cpp
    src/application/SessionControl.cpp
    src/application/AppLoop.cpp
    src/ui/Theme.cpp
    src/ui/Shell.cpp
    src/ui/MenuBar.cpp
    src/emu/Paths.cpp
    src/emu/FileBytes.cpp
    src/emu/Input.cpp
    src/emu/AudioOutput.cpp
    src/emu/ScreenTexture.cpp
    src/emu/GbaSession.cpp
    src/emu/NdsSession.cpp
    src/emu/NdsPlatformFiles.cpp
    src/emu/NdsPlatformSync.cpp
    src/emu/NdsPlatformStubs.cpp
    src/emu/NdsPlatformDynlib.cpp
    src/emu/NdsPlatformSave.cpp)

target_include_directories(emulocke PRIVATE src)
target_link_libraries(emulocke PRIVATE core mgba imgui SDL3::SDL3)
target_compile_definitions(emulocke PRIVATE SDL_MAIN_HANDLED)
get_target_property(MGBA_COMPILE_DEFS mgba COMPILE_DEFINITIONS)
if(MGBA_COMPILE_DEFS)
    target_compile_definitions(emulocke PRIVATE ${MGBA_COMPILE_DEFS})
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(emulocke PRIVATE dl pthread)
endif()
if(MSVC)
    target_compile_definitions(emulocke PRIVATE _CRT_SECURE_NO_WARNINGS NOMINMAX WIN32_LEAN_AND_MEAN)
    target_compile_options(emulocke PRIVATE /utf-8)
endif()
if(MINGW)
    target_link_options(emulocke PRIVATE -static-libgcc -static-libstdc++ -static)
endif()

add_custom_command(
    TARGET emulocke POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:emulocke>/assets)
