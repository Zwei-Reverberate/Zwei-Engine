project(db)

file(GLOB_RECURSE DB_SOURCES "src/*.cpp")
add_library(${PROJECT_NAME} STATIC ${DB_SOURCES})

target_link_libraries(${PROJECT_NAME} foundation)
target_link_libraries(${PROJECT_NAME} glm::glm)
target_link_libraries(${PROJECT_NAME} CGAL::CGAL)

target_include_directories(${PROJECT_NAME} PUBLIC .)