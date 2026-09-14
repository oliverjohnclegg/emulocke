set(EMULOCKE_SANITIZE "" CACHE STRING "Sanitizer build: empty, address (ASan+UBSan) or thread (TSan)")
set_property(CACHE EMULOCKE_SANITIZE PROPERTY STRINGS "" address thread)

if(NOT EMULOCKE_SANITIZE)
    return()
endif()

if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(FATAL_ERROR "EMULOCKE_SANITIZE requires GCC or Clang")
endif()

if(EMULOCKE_SANITIZE STREQUAL "address")
    set(EMULOCKE_SANITIZE_FLAGS "-fsanitize=address,undefined -fno-sanitize-recover=all")
elseif(EMULOCKE_SANITIZE STREQUAL "thread")
    set(EMULOCKE_SANITIZE_FLAGS "-fsanitize=thread")
else()
    message(FATAL_ERROR "EMULOCKE_SANITIZE must be address or thread, got '${EMULOCKE_SANITIZE}'")
endif()

set(EMULOCKE_SANITIZE_COMPILE "${EMULOCKE_SANITIZE_FLAGS} -fno-omit-frame-pointer -g -O1")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EMULOCKE_SANITIZE_COMPILE}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EMULOCKE_SANITIZE_COMPILE}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EMULOCKE_SANITIZE_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${EMULOCKE_SANITIZE_FLAGS}")

set(EMULOCKE_SANITIZER_SUPPRESSIONS "${CMAKE_SOURCE_DIR}/tools/sanitizers")
set(EMULOCKE_SANITIZER_TEST_ENV
    "ASAN_OPTIONS=detect_leaks=1:strict_string_checks=1:check_initialization_order=1:suppressions=${EMULOCKE_SANITIZER_SUPPRESSIONS}/asan.supp"
    "LSAN_OPTIONS=suppressions=${EMULOCKE_SANITIZER_SUPPRESSIONS}/lsan.supp"
    "UBSAN_OPTIONS=print_stacktrace=1:halt_on_error=1:suppressions=${EMULOCKE_SANITIZER_SUPPRESSIONS}/ubsan.supp"
    "TSAN_OPTIONS=halt_on_error=1:second_deadlock_stack=1")

function(emulocke_apply_sanitizer_test_env)
    get_property(tests DIRECTORY PROPERTY TESTS)
    foreach(test IN LISTS tests)
        set_property(TEST ${test} APPEND PROPERTY ENVIRONMENT ${EMULOCKE_SANITIZER_TEST_ENV})
    endforeach()
endfunction()
