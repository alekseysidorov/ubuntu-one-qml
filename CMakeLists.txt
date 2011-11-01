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

if(WIN32)
	set(BIN_DIR_DEF bin)
	set(SHARE_DIR_DEF share)
#ELSEIF(APPLE)
#	set(BIN_DIR_DEF Resources/share)
else()
	set(BIN_DIR_DEF bin)
	set(SHARE_DIR_DEF share/apps)
endif()

include(UseQt4)
include(MyMacro)

set(QT_MIN_VERSION "4.7.4")

add_subdirectory(3rdparty)
add_subdirectory(qmlbinding)
add_subdirectory(client)
