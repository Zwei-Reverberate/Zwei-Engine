project(foundation)

file(GLOB_RECURSE FOUNDATION_SOURCES "src/*.cpp")
add_library(${PROJECT_NAME} STATIC ${FOUNDATION_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC .)