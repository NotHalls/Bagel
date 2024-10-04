cmake_minimum_required(VERSION 3.30)

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
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin-objs/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}")


add_subdirectory(./submodules/glfw)

add_library(glad STATIC submodules/glad/src/glad.c)
target_include_directories(glad PUBLIC submodules/glad/include)

file(GLOB_RECURSE MAIN_SOURCES "./src/*.cpp")


add_executable(${PROJECT_NAME} ${MAIN_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    submodules/glfw/include
    submodules/glm/glm

    src
)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad)


target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_INCLUDE_NONE)

target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:BG_DEBUG>)
target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<CONFIG:Release>:BG_RELEASE>)