### eqmake4 was here ###
TEMPLATE = lib
TARGET = qmlbinding
QT += declarative
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = org.evernote.quick

# Input
SOURCES += \
    qmlbinding_plugin.cpp \
    quickevernote.cpp

HEADERS += \
    qmlbinding_plugin.h \
    quickevernote.h

OTHER_FILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
symbian {
    TARGET.EPOCALLOWDLLDATA = 1
} else:unix {
    maemo5 | !isEmpty(MEEGO_VERSION_MAJOR) {
        installPath = /usr/lib/qt4/imports/$$replace(uri, \\., /)
    } else {
        installPath = $$[QT_INSTALL_IMPORTS]/$$replace(uri, \\., /)
    }
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

CONFIG -= debug_and_release debug
CONFIG += release


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/kqoauth/src/ -lkqoauth
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rdparty/kqoauth/src/ -lkqoauthd
else:mac: LIBS += -F$$OUT_PWD/../3rdparty/kqoauth/src/ -framework kqoauth
else:symbian: LIBS += -lkqoauth
else:unix: LIBS += -L$$OUT_PWD/../3rdparty/kqoauth/src/ -lkqoauth

INCLUDEPATH += $$PWD/../3rdparty/kqoauth/src
DEPENDPATH += $$PWD/../3rdparty/kqoauth/src
