cmake_minimum_required(VERSION 3.5)

project(GadgetEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES   src/main.cpp
    src/scrollarea.h  src/scrollarea.cpp
    src/gridwidget.h  src/gridwidget.cpp
    src/gadgeteditorfactory.h src/gadgeteditorfactory.cpp
    editors/framegrided.h     editors/framegrided.cpp
    editors/gadgeteditor.h    editors/gadgeteditor.cpp
    editors/gadgeteditorstruct.h     editors/gadgeteditorstruct.cpp
    editors/gadgeteditorenumerator.h editors/gadgeteditorenumerator.cpp
    editors/gadgeteditordouble.h     editors/gadgeteditordouble.cpp
    editors/gadgeteditorinteger.h    editors/gadgeteditorinteger.cpp
    editors/gadgeteditorboolean.h    editors/gadgeteditorboolean.cpp
    ../common/gadgets/player.h       ../common/gadgets/player.cpp
    ../common/gadgets/p2d.h          ../common/gadgets/p2d.cpp
)


include_directories(../common src)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GadgetEditor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(GadgetEditor SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(GadgetEditor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(GadgetEditor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(GadgetEditor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GadgetEditor)
endif()
