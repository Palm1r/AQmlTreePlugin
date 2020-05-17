cmake_minimum_required(VERSION 3.5)

project(QmlTreeViewExample LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

add_executable(QmlTreeViewExample
    main.cpp
    qml.qrc
    tree_model.h
    tree_model.cpp
    tree_item.h
    tree_item.cpp)

target_compile_definitions(QmlTreeViewExample
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(QmlTreeViewExample
    PRIVATE Qt5::Core Qt5::Quick)
