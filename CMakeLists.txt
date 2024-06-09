cmake_minimum_required(VERSION 3.21)
project(ZW_RENDER)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#set(VCPKG_ROOT "D:/vcpkg") 
#set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_PREFIX_PATH "D:/Vcpkg/vcpkg/installed/x64-windows;D:/Qt/6.2.4/msvc2019_64")

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

find_package(tinyobjloader CONFIG REQUIRED)
if(NOT tinyobjloader_FOUND)
    message(FATAL_ERROR "tinyobjloader not found.")
endif()

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
if(NOT Qt6_FOUND)
    message(FATAL_ERROR "Qt6 not found.")
endif()


set (QT_FILE_PATH "D:/Qt/6.2.4/msvc2019_64")
file(GLOB QT_DLL_FILES ${QT_FILE_PATH}/bin/*.dll)
foreach(DLL_FILE ${QT_DLL_FILES})
    file(COPY ${DLL_FILE} DESTINATION ${EXECUTABLE_OUTPUT_PATH})
endforeach()
file(COPY ${QT_FILE_PATH}/plugins DESTINATION ${EXECUTABLE_OUTPUT_PATH})

set (GLFW_FILE_PATH "D:/Vcpkg/vcpkg/packages/glfw3_x64-windows")
file(GLOB GLFW_DLL_FILES ${GLFW_FILE_PATH}/bin/*.dll)
foreach(DLL_FILE ${GLFW_DLL_FILES})
    file(COPY ${DLL_FILE} DESTINATION ${EXECUTABLE_OUTPUT_PATH})
endforeach()

if(MSVC)
    # 关闭 C4530 警告（C++ 异常处理未启用）
    add_compile_options(/wd4530)
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/src/main)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/window)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/vulkan)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/renderdata)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/foundation)