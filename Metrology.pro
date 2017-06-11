#-------------------------------------------------
#
# Project created by QtCreator 2017-05-27T20:59:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Metrology
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += src/main.cpp\
    src/InputDialog.cpp \
    src/SeriesTable.cpp \
    src/TableModel.cpp \
    src/MainWindow.cpp \

HEADERS  += \
    include/InputDialog.h \
    include/SeriesTable.h \
    include/TableModel.h \
    include/MainWindow.h

FORMS    += \
    ui/InputDialog.ui \
    ui/MainWindow.ui

RESOURCES += \
    res/res.qrc

# RC_FILE = icon.rc
