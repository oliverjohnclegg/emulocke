if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    return()
endif()

set(EMULOCKE_HARDEN_LANGS "$<COMPILE_LANGUAGE:C,CXX>")

add_compile_options(
    "$<${EMULOCKE_HARDEN_LANGS}:-Wall;-Wextra;-Wformat=2;-fstack-protector-strong>")
add_compile_definitions("$<$<COMPILE_LANGUAGE:CXX>:_GLIBCXX_ASSERTIONS>")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    if(NOT EMULOCKE_SANITIZE)
        add_compile_options(
            "$<$<AND:${EMULOCKE_HARDEN_LANGS},$<NOT:$<CONFIG:Debug>>>:-U_FORTIFY_SOURCE;-D_FORTIFY_SOURCE=3>")
    endif()
    add_link_options(-Wl,-z,relro,-z,now)
endif()
