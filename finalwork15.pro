#-------------------------------------------------
#
# Project created by QtCreator 2015-06-04T14:57:30
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = finalwork15
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    functional_for_work_with_files.cpp \
    functional_for_work_with_database.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h

FORMS    += mainwindow.ui
QT       += printsupport
LIBS += -lpq -lglut -lGLU
