project(window)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src WINDOW_SOURCES)

add_library(${PROJECT_NAME} STATIC ${WINDOW_SOURCES})

target_link_libraries(${PROJECT_NAME} vulkan)
target_include_directories(${PROJECT_NAME} PUBLIC .)