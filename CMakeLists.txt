cmake_minimum_required(VERSION 3.16)

project(Library_Management_And_Routing VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake where Qt is located
set(CMAKE_PREFIX_PATH "C:/Qt/6.5.3/mingw_64/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

qt_add_executable(Library_Management_And_Routing
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}

)

target_link_libraries(Library_Management_And_Routing PRIVATE Qt6::Widgets)

qt_finalize_executable(Library_Management_And_Routing)
