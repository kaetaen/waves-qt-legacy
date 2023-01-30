cmake_minimum_required(VERSION 3.5)

project(Waves VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.ui
    mainwindow.h
    mainwindow.cpp)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Waves
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )


else()
    if(ANDROID)
        add_library(Waves SHARED
            ${PROJECT_SOURCES}
        )

    else()
        add_executable(Waves
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Waves PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

install(TARGETS Waves
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Waves)
endif()
