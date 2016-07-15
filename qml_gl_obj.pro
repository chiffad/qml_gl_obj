TEMPLATE = app

QT += qml quick

CONFIG += c++14

HEADERS += \
           headers/cubes.h \
         headers/fb_obj.h
SOURCES += src/main.cpp \
           src/cubes.cpp \
    src/fb_obj.cpp

RESOURCES += qml.qrc
