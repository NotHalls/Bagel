cmake_minimum_required(VERSION 3.29)

set(PROJECT_NAME Bagel)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


if(WIN32)
    add_compile_definitions(BG_WINDOWS)
elseif(UNIX)
    add_compile_definitions(BG_UNIX)
endif()


set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Choose a build type (Debug | Release)" FORCE)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose a build type (Debug | Release)" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/libs/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}")

add_subdirectory(./submodules/glfw)
add_subdirectory(./submodules/assimp)

set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_INSTALL OFF)

target_compile_definitions(assimp PUBLIC _CRT_SECURE_NO_WARNINGS)
target_compile_options(assimp PUBLIC -Wunknown-pragmas -Wno-unknown-pragmas)

add_library(glad STATIC submodules/glad/src/glad.c)
target_include_directories(glad PUBLIC submodules/glad/include)

add_library(imgui STATIC
    submodules/imgui/imconfig.h
    submodules/imgui/imgui.h
    submodules/imgui/imgui.cpp
    submodules/imgui/imgui_draw.cpp
    submodules/imgui/imgui_internal.h
    submodules/imgui/imgui_widgets.cpp
    submodules/imgui/imstb_rectpack.h
    submodules/imgui/imstb_textedit.h
    submodules/imgui/imstb_truetype.h
    submodules/imgui/imgui_demo.cpp
)
target_include_directories(imgui PUBLIC submodules/imgui)

file(GLOB_RECURSE MAIN_SOURCES "./src/*.cpp")
file(GLOB_RECURSE STBI_SOURCES "submodules/stb_image/*.cpp")


add_executable(${PROJECT_NAME} ${MAIN_SOURCES} ${STBI_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    submodules/glfw/include
    submodules/glm/glm
    submodules/stb_image
    submodules/assimp/include

    src
    src/Include
)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw imgui glad assimp)


target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_INCLUDE_NONE)

target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:BG_DEBUG>)
target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:Release>:BG_RELEASE>)