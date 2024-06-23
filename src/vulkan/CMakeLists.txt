project(vulkan)

file(GLOB_RECURSE VULKAN_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(${PROJECT_NAME} STATIC ${VULKAN_SOURCES})

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} ${VK_SDK_LIB})
target_link_libraries(${PROJECT_NAME} renderData)

target_include_directories(${PROJECT_NAME} PUBLIC ${VK_SDK_INCLUDE})
target_include_directories(${PROJECT_NAME} PUBLIC .)