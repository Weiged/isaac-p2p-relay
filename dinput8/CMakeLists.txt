cmake_minimum_required(VERSION 3.15)
project(dinput8_proxy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(dinput8 SHARED
    dinput8.cpp
    dinput8.def
)

if(MSVC)
    add_compile_options(/utf-8)

    target_compile_options(dinput8 PRIVATE
        /W3
        /GS-
        /Gy
    )

    target_link_options(dinput8 PRIVATE
        /DEF:${CMAKE_CURRENT_SOURCE_DIR}/dinput8.def
    )
endif()

set_target_properties(dinput8 PROPERTIES
    OUTPUT_NAME "dinput8"
    PREFIX ""
    SUFFIX ".dll"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${P2P_ARCH}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${P2P_ARCH}
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${P2P_ARCH}
)

target_link_libraries(dinput8 PRIVATE
    kernel32
)
