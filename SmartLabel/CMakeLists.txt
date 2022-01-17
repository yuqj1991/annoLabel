cmake_minimum_required(VERSION 3.5)

project(SmartLabel VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)



set(PROJECT_SOURCES
    annotations/annotationitem.cpp
    annotations/cubeannotationitem.cpp
    annotations/rectannotationitem.cpp
    annotations/segannotationitem.cpp
    canvas/canvas2d.cpp
    canvas/canvas3d.cpp
    canvas/canvasbase.cpp
    canvas/childcanvas3d.cpp
    common.cpp
    controllers/annotationcontainer.cpp
    controllers/filemanager.cpp
    controllers/labelmanager.cpp
    main.cpp
    mainwindow.cpp
    login.cpp
    custumtaskdialog.cpp
    widgets/customlistwidget.cpp
    widgets/labeldialog.cpp
    widgets/labellineedit.cpp
    defaultannodialog.cpp
    configannodialog.cpp
    taskdialog.cpp
    add_attribute_dialog.cpp
    firstpagedialog.cpp
    point_dialog.cpp)


set(PROJECT_HEADERS
    annotations/annotationitem.h
    annotations/cubeannotationitem.h
    annotations/rectannotationitem.h
    annotations/segannotationitem.h
    canvas/canvas2d.h
    canvas/canvas3d.h
    canvas/canvasbase.h
    canvas/childcanvas3d.h
    common.h
    controllers/annotationcontainer.h
    controllers/filemanager.h
    controllers/labelmanager.h
    mainwindow.h
    widgets/customlistwidget.h
    widgets/labeldialog.h
    widgets/labellineedit.h
    mainwindow.ui
    login.h
    login.ui
    custumtaskdialog.h
    custumtaskdialog.ui
    defaultannodialog.h
    defaultannodialog.ui
    configannodialog.h
    configannodialog.ui
    firstpagedialog.h
    firstpagedialog.ui
    taskdialog.h
    taskdialog.ui
    add_attribute_dialog.h
    attribute_dialog.ui
    wegits_common.h
    point_dialog.h
    point_dialog.ui
    resource.qrc
    )

include_directories(annotations canvas controllers widgets)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartLabel
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES} ${PROJECT_HEADERS}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SmartLabel APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    #qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(SmartLabel SHARED
            ${PROJECT_SOURCES} ${PROJECT_HEADERS}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SmartLabel
            ${PROJECT_SOURCES} ${PROJECT_HEADERS}
        )
    endif()

    #qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(SmartLabel PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(SmartLabel PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartLabel)
endif()
