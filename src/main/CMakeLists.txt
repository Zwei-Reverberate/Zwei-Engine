project(main)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} MAIN_SOURCES)
add_executable(${PROJECT_NAME} ${MAIN_SOURCES})

target_link_libraries(${PROJECT_NAME} window)