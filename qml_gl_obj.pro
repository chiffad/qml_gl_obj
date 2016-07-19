TEMPLATE = app

QT += qml quick

CONFIG += c++14

HEADERS += \
    headers/fb_obj.h \
    headers/cube_renderer.h

SOURCES += src/main.cpp \
    src/fb_obj.cpp \
    src/cube_renderer.cpp

RESOURCES += \
    qrs.qrc
