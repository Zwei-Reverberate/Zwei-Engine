project(window)

file(GLOB_RECURSE WINDOW_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE WINDOW_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

# moc 包含 Q_OBJECT 宏的头文件
set(HEADERS_WITH_QOBJECT)
foreach(header ${WINDOW_HEADERS})
    file(READ ${header} FILE_CONTENTS)
    if(FILE_CONTENTS MATCHES "Q_OBJECT")
        list(APPEND HEADERS_WITH_QOBJECT ${header})
    endif()
endforeach()

qt6_wrap_cpp(MOC_FILES ${HEADERS_WITH_QOBJECT})

set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTORCC ON)

add_library(${PROJECT_NAME} STATIC ${WINDOW_SOURCES} ${MOC_FILES})

target_link_libraries(${PROJECT_NAME} vulkan)
target_include_directories(${PROJECT_NAME} PUBLIC .)
target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Gui Qt6::Widgets)