#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QQmlApplicationEngine>
#include "headers/fbo_obj.h"

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  qmlRegisterType<Fbo_obj>("SceneGraphRendering", 1, 0, "Renderer");

  QQmlApplicationEngine engine("qml_gl_obj/res/main.qml");

  return app.exec();
}
