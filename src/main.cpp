#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "headers/fb_obj.h"
#include "headers/foo.h"

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  qmlRegisterType<Fb_obj>("SceneGraphRendering", 1, 0, "Renderer");

  QQmlApplicationEngine engine("qml_gl_obj/res/main.qml");
  Foo f;

  engine.rootContext()->setContextProperty("ContextProperty", &f);

  return app.exec();
}
