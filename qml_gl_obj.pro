TEMPLATE = app

QT += qml quick

CONFIG += c++14

HEADERS += \
         headers/logorenderer.h \
    headers/fb_obj.h

SOURCES += src/main.cpp \
           src/logorenderer.cpp \
    src/fb_obj.cpp

RESOURCES += \
    qrs.qrc
