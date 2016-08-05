TEMPLATE = app

QT += qml quick
QT += opengl

CONFIG += c++14

HEADERS += headers/fb_obj.h \
           headers/cube_renderer.h \
    headers/foo.h

SOURCES += src/main.cpp \
           src/fb_obj.cpp \
           src/cube_renderer.cpp

RESOURCES += qrs.qrc
