cmake_minimum_required(VERSION 3.21)
project(fear)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(EXTERNAL_LIBS_DIR ${PROJECT_SOURCE_DIR}/external)

add_executable(${PROJECT_NAME}
        main.cpp
        fear.cpp fear.hpp
        types.h
        queue_family_indices.hpp queue_family_indices.cpp
        )

add_subdirectory(${EXTERNAL_LIBS_DIR}/GLFW)
target_link_libraries(${PROJECT_NAME} glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

find_package(Vulkan REQUIRED)
if (VULKAN_FOUND)
    target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES})
    target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIR})
endif ()