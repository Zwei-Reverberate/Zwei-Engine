project(renderData)

file(GLOB_RECURSE RENDERDATA_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(${PROJECT_NAME} STATIC ${RENDERDATA_SOURCES})

target_link_libraries(${PROJECT_NAME} foundation)
target_link_libraries(${PROJECT_NAME} db)
target_link_libraries(${PROJECT_NAME} tinyobjloader::tinyobjloader)

target_include_directories(${PROJECT_NAME} PUBLIC .)