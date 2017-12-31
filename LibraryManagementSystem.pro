#-------------------------------------------------
#
# Project created by QtCreator 2017-12-31T12:34:19
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LibraryManagementSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aboutdialog.cpp \
    addbookdialog.cpp \
    addreaderdialog.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    addbookdialog.h \
    addreaderdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    addbookdialog.ui \
    addreaderdialog.ui
