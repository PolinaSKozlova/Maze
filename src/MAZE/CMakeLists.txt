cmake_minimum_required(VERSION 3.5)

project(MAZE VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MACOSX_BUNDLE_ICON_FILE MAZE.icns)
set(MY_APP_ICON_MACOSX ${CMAKE_CURRENT_SOURCE_DIR}/icons/MAZE.icns)
set_source_files_properties(${MY_APP_ICON_MACOSX} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
include_directories(maze_reader maze_creator cave_generator view)

set(PROJECT_SOURCES
    main.cc
    view/mainwindow.cc
    view/mainwindow.h
    view/mainwindow.ui
    view/mazewidget.h
    view/mazewidget.cc
    controller.h
    controller.cc
    maze_reader/maze_ordinary.cc
    maze_reader/maze_ordinary.h
    maze_creator/maze_ideal.cc
    maze_creator/maze_ideal.h
    maze_solution/maze_solution.h
    maze_solution/maze_solution.cc
    maze_struct.h
    cave_generator/cave.cc
    cave_generator/cave.h
    cave_generator/cave_generator.cc
    cave_generator/cave_generator.h
    view/cavewidget.cc
    view/cavewidget.h
    icons/cat.png
    icons/mouse.png
    icons/maze.png
    icons/MAZE.icns
    images.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MAZE
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${MY_APP_ICON_MACOSX}
    )

# Define target properties for Android with Qt 6 as:
# set_property(TARGET MAZE2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MAZE SHARED
            ${PROJECT_SOURCES}
            ${RESOURCES}
        )

    # Define properties for Android with Qt 5 after find_package() calls as:
    # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MAZE
            ${PROJECT_SOURCES}
            ${RESOURCES}
            ${MY_APP_ICON_MACOSX}
        )
    endif()
endif()

target_link_libraries(MAZE PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(MAZE PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MAZE)
endif()
