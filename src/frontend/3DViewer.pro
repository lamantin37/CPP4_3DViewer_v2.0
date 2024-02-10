QT += core gui
QT += 3dcore 3drender 3dinput 3dextras multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += \
        c++17
DEFINES += QT_DEPRECATED_WARNINGS

include(QtGifImage/src/gifimage/qtgifimage.pri)

SOURCES += \
    ../backend/s21_matrix/s21_matrix_oop_operations.cc \
    ../backend/s21_matrix/s21_matrix_oop_operators.cc \
    ../backend/s21_matrix/s21_matrix_oop.cc \
    ../backend/s21_parser.cc \
    ../backend/s21_transformations.cc \
    ../controller/s21_controller.cc \
    mainwindow.cc \
    settingswindow.cc \
    ../main.cc
HEADERS += \
    ../backend/auxiliary_modules.h \
    ../backend/s21_matrix/s21_matrix_oop.h \
    ../controller/s21_controller.h \
    mainwindow.h \
    settingswindow.h

FORMS += \
    MainWindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

DISTFILES +=
