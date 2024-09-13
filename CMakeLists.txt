cmake_minimum_required(VERSION 3.28)
project(feather)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Quick
        quickwidgets
        REQUIRED)

FILE(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)
FILE(GLOB_RECURSE RESOURCE_FILES src/*.qrc)

add_executable(feather  ${SOURCE_FILES} ${RESOURCE_FILES})
target_link_libraries(feather
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Quick
        Qt5::QuickWidgets
)

