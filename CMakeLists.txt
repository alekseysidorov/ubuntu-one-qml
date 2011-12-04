cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

if(COMMAND cmake_policy)
    cmake_policy (SET CMP0003 NEW)
endif(COMMAND cmake_policy)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(QT_USE_QTGUI true)
set(QT_USE_QTCORE true)
set(QT_USE_QTDECLARATIVE true)
set(QT_USE_QTNETWORK true)
set(QT_USE_QTXML true)
set(QT_USE_QTWEBKIT true)
set(QT_USE_QTSQL true)
set(CMAKE_AUTOMOC true)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
include(CommonUtils)

if(HARMATTAN)
	add_definitions(-DMEEGO_EDITION_HARMATTAN)
endif()

set(QT_MIN_VERSION "4.7.4")
define_bundle_paths(ubuntuNotes)

option(CREATE_BUNDLE "Create application bundle then install" OFF)

add_subdirectory(3rdparty)
add_subdirectory(qmlbinding)
add_subdirectory(client)
