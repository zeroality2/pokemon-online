#-------------------------------------------------
#
# Project created by QtCreator 2010-07-25T18:38:46
#
#-------------------------------------------------

QT +=
TARGET = StatsExtracter
DESTDIR = ../../bin

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
LIBS += -L../../bin -lpokemonlib

SOURCES += main.cpp