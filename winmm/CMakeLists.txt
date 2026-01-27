cmake_minimum_required(VERSION 3.15)
project(winmm_proxy)

# 强制使用 x86 (32位)
if(NOT CMAKE_GENERATOR_PLATFORM)
    set(CMAKE_GENERATOR_PLATFORM Win32)
endif()

# C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 创建 DLL
add_library(winmm SHARED
    winmm.cpp
    x86.def
)

# MSVC UTF-8 编码支持 (修复 C4819 警告)
add_compile_options(/utf-8)


# 输出文件名为 winmm.dll
set_target_properties(winmm PROPERTIES
    OUTPUT_NAME "winmm"
    PREFIX ""
    SUFFIX ".dll"
)

# MSVC 编译选项
if(MSVC)
    target_compile_options(winmm PRIVATE
        /W3         # 警告级别
        /GS-        # 禁用安全检查（减小体积）
        /Gy         # 启用函数级链接
    )
    
    target_link_options(winmm PRIVATE
        /DEF:${CMAKE_CURRENT_SOURCE_DIR}/x86.def
    )
endif()

# 链接 Windows 库
target_link_libraries(winmm PRIVATE
    kernel32
)
