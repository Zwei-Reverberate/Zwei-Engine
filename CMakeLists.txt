cmake_minimum_required(VERSION 3.21)
project(ZW_RENDER)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(VCPKG_ROOT "D:/vcpkg") 
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

if(NOT DEFINED ENV{VK_SDK_PATH})
    message(FATAL_ERROR "VK_SDK_PATH not defined!")
endif()
set(VK_SDK_PATH $ENV{VK_SDK_PATH})
set(VK_SDK_INCLUDE ${VK_SDK_PATH}/Include)
set(VK_SDK_LIB ${VK_SDK_PATH}/Lib/vulkan-1.lib)

find_package(glm CONFIG REQUIRED)
if(NOT glm_FOUND)
    message(FATAL_ERROR "glm not found.")
endif()

find_package(glfw3 CONFIG REQUIRED)
if(NOT glfw3_FOUND)
    message(FATAL_ERROR "glfw3 not found.")
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/src/main)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/window)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/vulkan)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/renderdata)