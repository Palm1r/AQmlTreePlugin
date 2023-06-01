cmake_minimum_required(VERSION 3.16)

project(aqmltreeplugin VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_QML_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_library(aqmltreeplugin STATIC)
qt_add_qml_module(aqmltreeplugin
    URI aqmltreeplugin
    VERSION 1.0
    QML_FILES
    TreeItem.qml
    ListItem.qml
    ModelItem.qml

    SOURCES
    sources/treeitem.h
    sources/treeitem.cpp
    sources/treemodel.h
    sources/treemodel.cpp
)

set_target_properties(aqmltreeplugin PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(aqmltreeplugin
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(aqmltreeplugin
    PRIVATE Qt6::Quick)

target_include_directories(aqmltreeplugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sources)

# Test
find_package(Qt6 COMPONENTS Test REQUIRED)

set(TEST_SOURCES
    tests/tst_treemodeltest.cpp
)
enable_testing()
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE Qt6::Test aqmltreepluginplugin)
target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sources)
add_test(NAME test COMMAND tests)

# Example Project
qt_add_executable(ExampleProject example/example.cpp)
qt_add_qml_module(ExampleProject
    URI ExampleProjectApp
    VERSION 1.0
    QML_FILES example/example.qml
    SOURCES example/rootcontroller.h example/rootcontroller.cpp
)
target_link_libraries(ExampleProject PRIVATE Qt6::Quick aqmltreepluginplugin)
target_include_directories(ExampleProject PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sources)
target_compile_definitions(ExampleProject PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
