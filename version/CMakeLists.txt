cmake_minimum_required(VERSION 3.15)
project(version_proxy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(version SHARED
    version.cpp
    version.def
)

if(MSVC)
    add_compile_options(/utf-8)

    target_compile_options(version PRIVATE
        /W3
        /GS-
        /Gy
    )

    target_link_options(version PRIVATE
        /DEF:${CMAKE_CURRENT_SOURCE_DIR}/version.def
    )
endif()

set_target_properties(version PROPERTIES
    OUTPUT_NAME "version"
    PREFIX ""
    SUFFIX ".dll"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${P2P_ARCH}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${P2P_ARCH}
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${P2P_ARCH}
)

target_link_libraries(version PRIVATE
    kernel32
)
