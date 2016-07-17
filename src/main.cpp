#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QQmlApplicationEngine>
#include "headers/fb_obj.h"

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  qmlRegisterType<Fb_obj>("SceneGraphRendering", 1, 0, "Renderer");

  QQmlApplicationEngine engine("qml_gl_obj/res/main.qml");

  return app.exec();
}
