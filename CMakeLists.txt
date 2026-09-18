cmake_minimum_required(VERSION 3.25)
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" EMULOCKE_VERSION)
string(STRIP "${EMULOCKE_VERSION}" EMULOCKE_VERSION)
project(emulocke VERSION ${EMULOCKE_VERSION} LANGUAGES C CXX)
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/BuildStamp.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Sanitizers.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Fuzzing.cmake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

if(MINGW)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    set(CURL_USE_STATIC_LIBS ON)
endif()

include(FetchContent)

find_package(SDL3 QUIET CONFIG)
if(NOT SDL3_FOUND)
    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG a96677bdf6b4acb84af4ec294e5f60a4e8cbbe03
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
        GIT_TAG 31db6474b5231c180bd4618c8c90e43af50c86d0
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
if(MINGW)
    find_package(ZLIB REQUIRED)
    target_compile_definitions(mgba PRIVATE HAVE_CRC32)
    set_property(TARGET mgba APPEND PROPERTY INTERFACE_LINK_LIBRARIES ${ZLIB_LIBRARIES})
endif()
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Hardening.cmake")

find_package(LibLZMA REQUIRED)
add_library(xdelta3 STATIC third_party/xdelta3/xdelta3.c)
set_target_properties(xdelta3 PROPERTIES C_STANDARD 11 C_STANDARD_REQUIRED ON)
target_include_directories(xdelta3 PUBLIC ${CMAKE_SOURCE_DIR}/third_party/xdelta3)
target_compile_definitions(xdelta3
    PUBLIC
        SIZEOF_SIZE_T=8
        SIZEOF_UNSIGNED_LONG_LONG=8
    PRIVATE
        XD3_MAIN=0
        SECONDARY_DJW=1
        SECONDARY_LZMA=1
        HAVE_LZMA_H=1
        XD3_HARDMAXWINSIZE=1073741824)
if(WIN32)
    target_compile_definitions(xdelta3 PUBLIC SIZEOF_UNSIGNED_LONG=4)
else()
    target_compile_definitions(xdelta3 PUBLIC SIZEOF_UNSIGNED_LONG=8)
endif()
target_link_libraries(xdelta3 PUBLIC LibLZMA::LibLZMA)
if(MINGW)
    target_compile_definitions(xdelta3 PUBLIC LZMA_API_STATIC)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(xdelta3 PRIVATE -w -include assert.h)
endif()
if(EMULOCKE_SANITIZE STREQUAL "address")
    target_compile_options(xdelta3 PRIVATE -fno-sanitize=undefined)
endif()

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

add_library(emulocke_calc STATIC
    src/calc/Type.cpp
    src/calc/Stats.cpp
    src/calc/Gen3Bp.cpp
    src/calc/Gen3Atk.cpp
    src/calc/Gen3Mods.cpp
    src/calc/Calculate.cpp
    src/calc/KoChance.cpp
    src/calc/Dex.cpp
    src/calc/Pack.cpp
    src/calc/Build.cpp
    src/calc/SwitchIn.cpp
    src/calc/SwitchInPick.cpp
    src/calc/SwitchInHits.cpp
    src/calc/Session.cpp
    src/calc/SessionSearch.cpp
    src/calc/Ai.cpp
    src/calc/Labels.cpp)
target_include_directories(emulocke_calc PUBLIC src)

add_library(emulocke_adapter STATIC
    src/adapter/Registry.cpp
    src/adapter/gen3/Charset.cpp
    src/adapter/gen3/BoxCrypt.cpp
    src/adapter/gen3/BoxFields.cpp
    src/adapter/gen3/BoxMon.cpp
    src/adapter/gen3/MonFacts.cpp
    src/adapter/gen3/BoxHeader.cpp
    src/adapter/frlg/FrlgSave.cpp
    src/adapter/frlg/CfruExpanded.cpp
    src/adapter/frlg/FrlgFill.cpp
    src/adapter/frlg/FrlgLive.cpp
    src/adapter/frlg/FrlgBattle.cpp
    src/adapter/frlg/FrlgAdapter.cpp
    src/adapter/frlg/SpeciesNames.cpp
    src/adapter/frlg/SpeciesRef.cpp
    src/adapter/frlg/MapNames.cpp
    src/adapter/rse/RseSave.cpp
    src/adapter/rse/RseFill.cpp
    src/adapter/rse/RseLive.cpp
    src/adapter/rse/RseBattle.cpp
    src/adapter/rse/RseAdapter.cpp
    src/adapter/gen45/Names.cpp
    src/adapter/gen45/SpeciesRef.cpp
    src/adapter/gen45/Crypto.cpp
    src/adapter/gen45/Text.cpp
    src/adapter/gen45/Parse.cpp
    src/adapter/gen45/NdsBattle.cpp
    src/adapter/gen45/NdsBattleParty.cpp
    src/adapter/gen45/NdsBattleScan.cpp
    src/adapter/gen4/Save.cpp
    src/adapter/gen4/Battle.cpp
    src/adapter/dppt/DpptAdapter.cpp
    src/adapter/hgss/HgssAdapter.cpp
    src/adapter/gen5/Save.cpp
    src/adapter/gen5/Battle.cpp
    src/adapter/gen5/Pokeparam.cpp
    src/adapter/gen5/PokeparamHp.cpp
    src/adapter/gen5/PokeparamScan.cpp
    src/adapter/gen5/PokeparamTag.cpp
    src/adapter/bw/BwAdapter.cpp)
target_include_directories(emulocke_adapter PUBLIC src)

file(GLOB EMULOCKE_TRACKER_ATLASES CONFIGURE_DEPENDS
    src/tracker/rse/*.cpp
    src/tracker/dp/*.cpp
    src/tracker/pt/*.cpp
    src/tracker/hgss/*.cpp
    src/tracker/bw/*.cpp
    src/tracker/b2w2/*.cpp
    src/tracker/blazevolt/*.cpp
    src/tracker/vw2/*.cpp
    src/tracker/sacredgold/*.cpp
    src/tracker/renegade/*.cpp
    src/tracker/emkaizo/*.cpp
    src/tracker/runbun/*.cpp
    src/tracker/incem/*.cpp
    src/tracker/rr/*.cpp
    src/tracker/unbound/*.cpp
    src/tracker/fro/*.cpp
    src/tracker/pkaizo/*.cpp)
add_library(emulocke_tracker STATIC
    src/tracker/Atlas.cpp
    src/tracker/Difficulty.cpp
    src/tracker/DifficultyChoices.cpp
    src/tracker/Log.cpp
    src/tracker/LogIo.cpp
    src/tracker/Fill.cpp
    src/tracker/Snap.cpp
    src/tracker/frlg/Stops.cpp
    src/tracker/frlg/Teams.cpp
    ${EMULOCKE_TRACKER_ATLASES})
target_include_directories(emulocke_tracker PUBLIC src)
target_link_libraries(emulocke_tracker PUBLIC emulocke_adapter)

add_library(emulocke_dex STATIC
    src/poke/Dex.cpp
    src/poke/Level.cpp
    src/poke/Showdown.cpp)
target_include_directories(emulocke_dex PUBLIC src)

find_package(CURL REQUIRED)
if(MINGW AND NOT TARGET CURL::libcurl_static)
    find_package(PkgConfig REQUIRED)
    set(PKG_CONFIG_ARGN "--static")
    pkg_check_modules(PC_CURL REQUIRED IMPORTED_TARGET libcurl)
endif()
add_library(emulocke_sprites STATIC
    src/poke/SpriteIndex.cpp
    src/poke/SlugLabel.cpp
    src/poke/SpriteUrls.cpp
    src/poke/HttpGet.cpp
    src/poke/SpriteCache.cpp
    src/cart/GameIndex.cpp
    src/cart/GameIndexSlug.cpp
    src/cart/GameArtPng.cpp
    src/cart/RgbaFit.cpp
    src/cart/GameArtCanvas.cpp
    src/cart/GameArtPlate.cpp
    src/cart/GameArtCache.cpp)
target_include_directories(emulocke_sprites PUBLIC src PRIVATE ${CMAKE_SOURCE_DIR}/third_party/stb)
if(MINGW AND TARGET CURL::libcurl_static)
    target_link_libraries(emulocke_sprites PUBLIC CURL::libcurl_static)
elseif(MINGW)
    target_link_libraries(emulocke_sprites PUBLIC PkgConfig::PC_CURL)
else()
    target_link_libraries(emulocke_sprites PUBLIC CURL::libcurl)
endif()
if(MINGW)
    target_compile_definitions(emulocke_sprites PUBLIC CURL_STATICLIB)
endif()

add_executable(emulocke
    src/main.cpp
    src/application/BuildId.cpp
    src/application/Host.cpp
    src/application/SdlRuntime.cpp
    src/application/Application.cpp
    src/application/ApplicationDialogs.cpp
    src/application/ApplicationCalc.cpp
    src/application/ApplicationCheats.cpp
    src/application/ApplicationPlay.cpp
    src/application/ApplicationPrefs.cpp
    src/application/ApplicationTracker.cpp
    src/application/PreviewSuite.cpp
    src/application/PreviewMons.cpp
    src/application/SessionControl.cpp
    src/application/AppLoop.cpp
    src/application/Prefs.cpp
    src/application/PrefsParse.cpp
    src/application/RunControl.cpp
    src/ui/Theme.cpp
    src/ui/KitKeys.cpp
    src/ui/KitNav.cpp
    src/ui/Shell.cpp
    src/ui/GbaPartyScreen.cpp
    src/ui/GbaPartySlot.cpp
    src/ui/Home.cpp
    src/ui/HomeKit.cpp
    src/ui/NewRunModal.cpp
    src/ui/NewRunKit.cpp
    src/ui/NewRunOptions.cpp
    src/ui/PresetPicker.cpp
    src/ui/GamePicker.cpp
    src/ui/GameStrip.cpp
    src/ui/GameStripDraw.cpp
    src/ui/GameArtGpu.cpp
    src/ui/LoadingRunModal.cpp
    src/ui/NewAttemptConfirm.cpp
    src/ui/DeleteRunConfirm.cpp
    src/ui/RunList.cpp
    src/ui/Suite.cpp
    src/ui/Tracker.cpp
    src/ui/TrackerKit.cpp
    src/ui/TrackerRow.cpp
    src/ui/TrackerMarks.cpp
    src/ui/TrackerKindTip.cpp
    src/ui/TrackerStatus.cpp
    src/ui/BoxSprites.cpp
    src/ui/FieldLog.cpp
    src/ui/Calculator.cpp
    src/ui/CalculatorKit.cpp
    src/ui/CalculatorSearch.cpp
    src/ui/CalculatorStrip.cpp
    src/ui/CalculatorWell.cpp
    src/ui/CalculatorMatchup.cpp
    src/ui/CalculatorHead.cpp
    src/ui/CalculatorMoves.cpp
    src/ui/CalculatorMoveLine.cpp
    src/ui/CalculatorMoveRow.cpp
    src/ui/CalculatorKo.cpp
    src/ui/CalculatorField.cpp
    src/ui/CalculatorStamp.cpp
    src/ui/CalculatorStamps.cpp
    src/ui/CalculatorChip.cpp
    src/ui/Cheats.cpp
    src/ui/CheatsAdd.cpp
    src/ui/CheatsDraft.cpp
    src/ui/Pokemon.cpp
    src/ui/PokemonCopy.cpp
    src/ui/PokemonGather.cpp
    src/ui/PokemonParty.cpp
    src/ui/PokemonBox.cpp
    src/ui/PokemonWell.cpp
    src/ui/PokemonHover.cpp
    src/ui/MenuBar.cpp
    src/ui/HelpPopups.cpp
    src/ui/ControlsModal.cpp
    src/ui/RunStrip.cpp
    src/ui/RunStripDraw.cpp
    src/ui/IconAction.cpp
    src/ui/PngCache.cpp
    src/ui/MediaFetch.cpp
    src/emu/Paths.cpp
    src/emu/FileBytes.cpp
    src/emu/RamCapture.cpp
    src/emu/Input.cpp
    src/emu/KeyMap.cpp
    src/emu/AudioOutput.cpp
    src/emu/ScreenTexture.cpp
    src/emu/GbaSession.cpp
    src/emu/GbaCheats.cpp
    src/emu/NdsSession.cpp
    src/emu/NdsCheats.cpp
    src/emu/NdsPlatformFiles.cpp
    src/emu/NdsPlatformLocal.cpp
    src/emu/NdsPlatformSync.cpp
    src/emu/NdsPlatformStubs.cpp
    src/emu/NdsPlatformDynlib.cpp
    src/emu/NdsPlatformSave.cpp
    src/run/NdsMac.cpp
    src/run/BatteryWatch.cpp
    src/run/Catalog.cpp
    src/run/CatalogLookup.cpp
    src/run/CatalogFormat.cpp
    src/run/NuzlockeRules.cpp
    src/run/PatchApply.cpp
    src/run/PatchBps.cpp
    src/run/BpsCommands.cpp
    src/run/PatchXdelta.cpp
    src/run/RomLibrary.cpp
    src/run/RomLibraryEnsure.cpp
    src/run/RunLabel.cpp
    src/run/RunMeta.cpp
    src/run/RunMetaWrite.cpp
    src/run/RunStore.cpp
    src/run/RunStoreAttempts.cpp
    src/run/SavePeek.cpp
    src/run/TitlePlay.cpp
    src/cheats/Lines.cpp
    src/cheats/Uuid.cpp
    src/cheats/Book.cpp
    src/cheats/BookIo.cpp
    src/cheats/BookEnabled.cpp)

add_custom_target(emulocke-assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:emulocke>/assets)

target_include_directories(emulocke PRIVATE src)
target_link_libraries(emulocke PRIVATE emulocke_adapter emulocke_calc emulocke_tracker emulocke_dex emulocke_sprites core mgba xdelta3 imgui SDL3::SDL3)
target_compile_definitions(emulocke PRIVATE SDL_MAIN_HANDLED)
emulocke_stamp_target(emulocke)
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
if(WIN32)
    enable_language(RC)
    if(EMULOCKE_CHANNEL STREQUAL "stable")
        set(EMULOCKE_WIN_ICON assets/icons/emulocke.rc)
    else()
        set(EMULOCKE_WIN_ICON assets/icons/emulocke-vanguard.rc)
    endif()
    target_sources(emulocke PRIVATE ${EMULOCKE_WIN_ICON})
    set_source_files_properties(${EMULOCKE_WIN_ICON} PROPERTIES
        INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/assets/icons")
endif()

add_executable(emulocke-sprite-check
    src/test/sprite_check.cpp
    src/emu/Paths.cpp)
target_include_directories(emulocke-sprite-check PRIVATE src)
target_compile_definitions(emulocke-sprite-check PRIVATE SDL_MAIN_HANDLED)
target_link_libraries(emulocke-sprite-check PRIVATE emulocke_sprites SDL3::SDL3)
if(UNIX AND NOT APPLE)
    target_link_libraries(emulocke-sprite-check PRIVATE pthread)
endif()
add_dependencies(emulocke-sprite-check emulocke-assets)

add_executable(emulocke-game-art-check
    src/test/game_art_check.cpp
    src/emu/Paths.cpp)
target_include_directories(emulocke-game-art-check PRIVATE src)
target_compile_definitions(emulocke-game-art-check PRIVATE SDL_MAIN_HANDLED)
target_link_libraries(emulocke-game-art-check PRIVATE emulocke_sprites SDL3::SDL3)
if(UNIX AND NOT APPLE)
    target_link_libraries(emulocke-game-art-check PRIVATE pthread)
endif()
add_dependencies(emulocke-game-art-check emulocke-assets)

add_executable(emulocke-media-check
    src/test/media_check.cpp
    src/test/slug_check.cpp
    src/emu/FileBytes.cpp)
target_include_directories(emulocke-media-check PRIVATE src)
target_link_libraries(emulocke-media-check PRIVATE emulocke_sprites)

add_executable(emulocke-lifetime-check
    src/test/lifetime_check.cpp
    src/test/local_files_check.cpp
    src/application/BuildId.cpp
    src/application/Host.cpp
    src/application/SdlRuntime.cpp
    src/emu/AudioOutput.cpp
    src/emu/FileBytes.cpp
    src/emu/NdsPlatformFiles.cpp
    src/emu/NdsPlatformLocal.cpp
    src/emu/Paths.cpp
    src/emu/ScreenTexture.cpp)
target_include_directories(emulocke-lifetime-check PRIVATE src third_party/melonDS/src)
target_compile_definitions(emulocke-lifetime-check PRIVATE SDL_MAIN_HANDLED)
target_link_libraries(emulocke-lifetime-check PRIVATE imgui SDL3::SDL3)
emulocke_stamp_target(emulocke-lifetime-check)
if(UNIX AND NOT APPLE)
    target_link_libraries(emulocke-lifetime-check PRIVATE dl pthread)
endif()

add_executable(emulocke-gba-check
    src/test/gba_host_check.cpp
    src/emu/GbaSession.cpp
    src/emu/GbaCheats.cpp
    src/emu/FileBytes.cpp
    src/emu/AudioOutput.cpp
    src/cheats/Lines.cpp)
target_include_directories(emulocke-gba-check PRIVATE src)
target_link_libraries(emulocke-gba-check PRIVATE mgba SDL3::SDL3)
if(MGBA_COMPILE_DEFS)
    target_compile_definitions(emulocke-gba-check PRIVATE ${MGBA_COMPILE_DEFS})
endif()
if(UNIX AND NOT APPLE)
    target_link_libraries(emulocke-gba-check PRIVATE dl pthread)
endif()

add_executable(emulocke-adapter-check
    src/test/adapter_check.cpp
    src/test/gen3_codec_check.cpp
    src/test/frlg_adapter_check.cpp
    src/test/frlg_difficulty_check.cpp
    src/test/rse_adapter_check.cpp
    src/test/gen4_adapter_check.cpp
    src/test/gen4_battle_check.cpp
    src/test/gen5_adapter_check.cpp
    src/test/gen5_battle_check.cpp
    src/test/save_bounds_check.cpp
    src/test/battery_watch_check.cpp
    src/test/SnapshotContract.cpp
    src/test/snapshot_fixtures.cpp
    src/test/snapshot_contract_check.cpp
    src/test/local_sav_check.cpp
    src/emu/FileBytes.cpp
    src/run/BatteryWatch.cpp)
target_include_directories(emulocke-adapter-check PRIVATE src)
target_link_libraries(emulocke-adapter-check PRIVATE emulocke_adapter)

add_executable(emulocke-tracker-check
    src/test/tracker_check.cpp
    src/test/tracker_atlas_check.cpp
    src/test/tracker_fill_check.cpp
    src/test/tracker_rival_fill_check.cpp
    src/test/preview_suite_check.cpp
    src/test/tracker_snap_check.cpp
    src/application/PreviewSuite.cpp
    src/application/PreviewMons.cpp
    src/run/Catalog.cpp)
target_include_directories(emulocke-tracker-check PRIVATE src)
target_link_libraries(emulocke-tracker-check PRIVATE emulocke_tracker emulocke_adapter)

add_executable(emulocke-poke-check
    src/test/poke_check.cpp)
target_include_directories(emulocke-poke-check PRIVATE src)
target_link_libraries(emulocke-poke-check PRIVATE emulocke_dex)

add_executable(emulocke-frlg-live-check EXCLUDE_FROM_ALL
    src/test/frlg_live_check.cpp
    src/emu/GbaSession.cpp
    src/emu/GbaCheats.cpp
    src/emu/FileBytes.cpp
    src/emu/AudioOutput.cpp
    src/cheats/Lines.cpp)
target_include_directories(emulocke-frlg-live-check PRIVATE src)
target_link_libraries(emulocke-frlg-live-check PRIVATE emulocke_adapter mgba SDL3::SDL3)
if(MGBA_COMPILE_DEFS)
    target_compile_definitions(emulocke-frlg-live-check PRIVATE ${MGBA_COMPILE_DEFS})
endif()
if(UNIX AND NOT APPLE)
    target_link_libraries(emulocke-frlg-live-check PRIVATE dl pthread)
endif()

add_executable(emulocke-boot-check EXCLUDE_FROM_ALL
    src/test/boot_roms_check.cpp
    src/emu/GbaSession.cpp
    src/emu/GbaCheats.cpp
    src/emu/NdsSession.cpp
    src/emu/NdsCheats.cpp
    src/run/NdsMac.cpp
    src/cheats/Lines.cpp
    src/emu/NdsPlatformFiles.cpp
    src/emu/NdsPlatformLocal.cpp
    src/emu/NdsPlatformSync.cpp
    src/emu/NdsPlatformStubs.cpp
    src/emu/NdsPlatformDynlib.cpp
    src/emu/NdsPlatformSave.cpp
    src/emu/FileBytes.cpp
    src/emu/AudioOutput.cpp
    src/emu/Paths.cpp
    src/run/Catalog.cpp
    src/run/CatalogLookup.cpp
    src/run/PatchApply.cpp
    src/run/PatchBps.cpp
    src/run/BpsCommands.cpp
    src/run/PatchXdelta.cpp)
target_include_directories(emulocke-boot-check PRIVATE src)
target_compile_definitions(emulocke-boot-check PRIVATE SDL_MAIN_HANDLED)
target_link_libraries(emulocke-boot-check PRIVATE emulocke_adapter core mgba xdelta3 SDL3::SDL3)
if(MGBA_COMPILE_DEFS)
    target_compile_definitions(emulocke-boot-check PRIVATE ${MGBA_COMPILE_DEFS})
endif()
if(UNIX AND NOT APPLE)
    target_link_libraries(emulocke-boot-check PRIVATE dl pthread)
endif()

add_executable(emulocke-run-check
    src/test/run_check.cpp
    src/test/BuildIdChecks.cpp
    src/application/BuildId.cpp
    src/emu/FileBytes.cpp
    src/emu/RamCapture.cpp
    src/run/Catalog.cpp
    src/run/CatalogLookup.cpp
    src/run/CatalogFormat.cpp
    src/run/NuzlockeRules.cpp
    src/run/PatchApply.cpp
    src/run/PatchBps.cpp
    src/run/BpsCommands.cpp
    src/run/PatchXdelta.cpp
    src/run/RomLibrary.cpp
    src/run/RomLibraryEnsure.cpp
    src/run/RunLabel.cpp
    src/run/NdsMac.cpp
    src/run/RunMeta.cpp
    src/run/RunMetaWrite.cpp
    src/run/RunStore.cpp
    src/run/RunStoreAttempts.cpp
    src/run/TitlePlay.cpp
    src/test/patch_format_check.cpp
    src/test/patch_bounds_check.cpp
    src/test/file_bytes_check.cpp
    src/test/ram_capture_check.cpp
    src/test/prefs_check.cpp
    src/test/cheats_check.cpp
    src/application/PrefsParse.cpp
    src/cheats/Lines.cpp
    src/cheats/Uuid.cpp
    src/cheats/Book.cpp
    src/cheats/BookIo.cpp
    src/cheats/BookEnabled.cpp
    src/emu/Paths.cpp
    src/test/local_patch_check.cpp
    src/test/layout_check.cpp
    src/test/input_check.cpp
    src/emu/KeyMap.cpp)
target_include_directories(emulocke-run-check PRIVATE src)
target_compile_definitions(emulocke-run-check PRIVATE SDL_MAIN_HANDLED)
target_link_libraries(emulocke-run-check PRIVATE mgba xdelta3 SDL3::SDL3)
emulocke_stamp_target(emulocke-run-check)
if(MGBA_COMPILE_DEFS)
    target_compile_definitions(emulocke-run-check PRIVATE ${MGBA_COMPILE_DEFS})
endif()
if(UNIX AND NOT APPLE)
    target_link_libraries(emulocke-run-check PRIVATE dl pthread)
endif()

add_executable(emulocke-fuzz-seeds EXCLUDE_FROM_ALL
    src/fuzz/SeedWriter.cpp
    src/test/snapshot_fixtures.cpp
    src/emu/FileBytes.cpp)
target_include_directories(emulocke-fuzz-seeds PRIVATE src)
target_link_libraries(emulocke-fuzz-seeds PRIVATE emulocke_adapter mgba xdelta3)
if(MGBA_COMPILE_DEFS)
    target_compile_definitions(emulocke-fuzz-seeds PRIVATE ${MGBA_COMPILE_DEFS})
endif()

if(EMULOCKE_FUZZ)
    set(EMULOCKE_PATCH_SOURCES
        src/run/PatchApply.cpp
        src/run/PatchBps.cpp
        src/run/BpsCommands.cpp
        src/run/PatchXdelta.cpp)
    foreach(harness fuzz_bps fuzz_xdelta fuzz_ips)
        emulocke_add_fuzzer(${harness} ${EMULOCKE_PATCH_SOURCES})
        target_link_libraries(${harness} PRIVATE mgba xdelta3)
        if(MGBA_COMPILE_DEFS)
            target_compile_definitions(${harness} PRIVATE ${MGBA_COMPILE_DEFS})
        endif()
    endforeach()
    foreach(harness fuzz_gen3_save fuzz_gen4_save fuzz_gen5_save fuzz_pk45 fuzz_btl_pokeparam)
        emulocke_add_fuzzer(${harness})
        target_link_libraries(${harness} PRIVATE emulocke_adapter)
    endforeach()
endif()

add_executable(emulocke-calc-check src/test/calc_check.cpp)
target_include_directories(emulocke-calc-check PRIVATE src)
target_link_libraries(emulocke-calc-check PRIVATE emulocke_calc)

add_executable(emulocke-calc-pack-check src/test/calc_pack_check.cpp)
target_include_directories(emulocke-calc-pack-check PRIVATE src)
target_link_libraries(emulocke-calc-pack-check PRIVATE emulocke_calc)

add_executable(emulocke-calc-blaze-check src/test/calc_blaze_check.cpp)
target_include_directories(emulocke-calc-blaze-check PRIVATE src)
target_link_libraries(emulocke-calc-blaze-check PRIVATE emulocke_calc)

enable_testing()
add_test(NAME adapter COMMAND emulocke-adapter-check)
add_test(NAME tracker COMMAND emulocke-tracker-check)
add_test(NAME poke COMMAND emulocke-poke-check)
add_test(NAME media COMMAND emulocke-media-check)
add_test(NAME lifetime COMMAND emulocke-lifetime-check)
add_test(NAME gba-host COMMAND emulocke-gba-check)
add_test(NAME run COMMAND emulocke-run-check)
add_test(NAME calc COMMAND emulocke-calc-check)
add_test(NAME calc-pack COMMAND emulocke-calc-pack-check)
add_test(NAME calc-blaze COMMAND emulocke-calc-blaze-check)
if(EMULOCKE_SANITIZE)
    emulocke_apply_sanitizer_test_env()
endif()

add_dependencies(emulocke emulocke-assets)
