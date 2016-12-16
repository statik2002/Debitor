#-------------------------------------------------
#
# Project created by QtCreator 2016-11-11T13:16:18
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = classTests
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    childwindow.cpp \
    firmsdialog.cpp \
    addfirmdialog.cpp \
    addcreditdialog.cpp \
    adddebetdialog.cpp \
    deletefirmdialog.cpp

HEADERS  += mainwindow.h \
    database.h \
    childwindow.h \
    firmsdialog.h \
    addfirmdialog.h \
    addcreditdialog.h \
    adddebetdialog.h \
    deletefirmdialog.h

FORMS    += mainwindow.ui \
    firmsdialog.ui \
    addfirmdialog.ui \
    addcreditdialog.ui \
    adddebetdialog.ui \
    deletefirmdialog.ui
