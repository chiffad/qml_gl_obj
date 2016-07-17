TEMPLATE = app

QT += qml quick

CONFIG += c++14

HEADERS += \
         headers/logorenderer.h \
    headers/fbo_obj.h

SOURCES += src/main.cpp \
           src/logorenderer.cpp \
    src/fbo_obj.cpp

RESOURCES += \
    qrs.qrc
