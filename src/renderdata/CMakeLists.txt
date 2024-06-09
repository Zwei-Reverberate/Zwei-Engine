project(renderData)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src RENDERDATA_SOURCES)
add_library(${PROJECT_NAME} STATIC ${RENDERDATA_SOURCES})

target_link_libraries(${PROJECT_NAME} glm::glm)
target_link_libraries(${PROJECT_NAME} tinyobjloader::tinyobjloader)

target_include_directories(${PROJECT_NAME} PUBLIC .)