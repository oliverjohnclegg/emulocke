set(EMULOCKE_CHANNEL "" CACHE STRING "stable or vanguard")
set(EMULOCKE_GIT_HASH "" CACHE STRING "short git hash")

if(EMULOCKE_CHANNEL STREQUAL "")
    if(DEFINED ENV{GITHUB_REF} AND "$ENV{GITHUB_REF}" STREQUAL "refs/heads/main")
        set(EMULOCKE_CHANNEL stable)
    elseif(DEFINED ENV{GITHUB_REF} AND NOT "$ENV{GITHUB_REF}" STREQUAL "")
        set(EMULOCKE_CHANNEL vanguard)
    else()
        execute_process(
            COMMAND git rev-parse --abbrev-ref HEAD
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            OUTPUT_VARIABLE EMULOCKE_GIT_BRANCH
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET)
        if(EMULOCKE_GIT_BRANCH STREQUAL "main")
            set(EMULOCKE_CHANNEL stable)
        else()
            set(EMULOCKE_CHANNEL vanguard)
        endif()
    endif()
endif()
string(TOLOWER "${EMULOCKE_CHANNEL}" EMULOCKE_CHANNEL)

if(EMULOCKE_GIT_HASH STREQUAL "")
    if(DEFINED ENV{GITHUB_SHA} AND NOT "$ENV{GITHUB_SHA}" STREQUAL "")
        string(SUBSTRING "$ENV{GITHUB_SHA}" 0 7 EMULOCKE_GIT_HASH)
    else()
        execute_process(
            COMMAND git rev-parse HEAD
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            OUTPUT_VARIABLE EMULOCKE_GIT_FULL
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET)
        if(EMULOCKE_GIT_FULL)
            string(SUBSTRING "${EMULOCKE_GIT_FULL}" 0 7 EMULOCKE_GIT_HASH)
        endif()
    endif()
endif()
if(EMULOCKE_GIT_HASH STREQUAL "")
    set(EMULOCKE_GIT_HASH unknown)
endif()

if(NOT EMULOCKE_VERSION)
    set(EMULOCKE_VERSION "${PROJECT_VERSION}")
endif()

if(WIN32)
    set(EMULOCKE_DIST_OS win-x64)
    set(EMULOCKE_DIST_EXT ".exe")
else()
    set(EMULOCKE_DIST_OS linux-x64)
    set(EMULOCKE_DIST_EXT "")
endif()

if(EMULOCKE_CHANNEL STREQUAL "stable")
    set(EMULOCKE_DIST_NAME "emulocke-v${EMULOCKE_VERSION}-${EMULOCKE_DIST_OS}${EMULOCKE_DIST_EXT}")
else()
    set(EMULOCKE_DIST_NAME "emulocke-vanguard-${EMULOCKE_GIT_HASH}-${EMULOCKE_DIST_OS}${EMULOCKE_DIST_EXT}")
endif()

file(WRITE "${CMAKE_BINARY_DIR}/dist-name.txt" "${EMULOCKE_DIST_NAME}\n")
file(WRITE "${CMAKE_BINARY_DIR}/identity.txt"
    "channel=${EMULOCKE_CHANNEL}\nversion=${EMULOCKE_VERSION}\nhash=${EMULOCKE_GIT_HASH}\ndist=${EMULOCKE_DIST_NAME}\n")
message(STATUS "Emulocke ${EMULOCKE_CHANNEL} ${EMULOCKE_DIST_NAME}")

macro(emulocke_stamp_target target)
    target_compile_definitions(${target} PRIVATE
        EMULOCKE_VERSION="${EMULOCKE_VERSION}"
        EMULOCKE_GIT_HASH="${EMULOCKE_GIT_HASH}")
    if(EMULOCKE_CHANNEL STREQUAL "stable")
        target_compile_definitions(${target} PRIVATE EMULOCKE_STABLE=1)
    endif()
endmacro()
