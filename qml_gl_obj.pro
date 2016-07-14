TEMPLATE = app

QT += qml quick \
      widgets
CONFIG += c++14

HEADERS += headers/glwidget.h
SOURCES += src/main.cpp \
           src/glwidget.cpp

RESOURCES += qml.qrc
