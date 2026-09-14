option(EMULOCKE_FUZZ "Build libFuzzer harnesses under src/fuzz (Clang only, needs EMULOCKE_SANITIZE=address)" OFF)

if(NOT EMULOCKE_FUZZ)
    return()
endif()

if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(FATAL_ERROR "EMULOCKE_FUZZ needs Clang: configure with -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++")
endif()
if(NOT EMULOCKE_SANITIZE STREQUAL "address")
    message(FATAL_ERROR "EMULOCKE_FUZZ needs -DEMULOCKE_SANITIZE=address so crashes surface as ASan/UBSan reports")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=fuzzer-no-link")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=fuzzer-no-link")

add_custom_target(fuzzers)

function(emulocke_add_fuzzer name)
    add_executable(${name} EXCLUDE_FROM_ALL src/fuzz/${name}.cpp ${ARGN})
    target_include_directories(${name} PRIVATE src)
    target_link_options(${name} PRIVATE -fsanitize=fuzzer)
    add_dependencies(fuzzers ${name})
endfunction()
