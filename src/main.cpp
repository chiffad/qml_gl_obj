#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "headers/fb_obj.h"
#include "headers/foo.h"

bool is_gui_quit = false;
void gui_is_quit();

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  qmlRegisterType<Fb_obj>("SceneGraphRendering", 1, 0, "Renderer");

  QQmlApplicationEngine engine("../qml_gl_obj/res/main.qml");
  Foo f;

  engine.rootContext()->setContextProperty("ContextProperty", &f);

  while(!is_gui_quit)
  {
    app.processEvents();

    if(app.allWindows().isEmpty() || !app.allWindows().last()->visibility())
      gui_is_quit();
  }

  return 0;
}

void gui_is_quit()
{
  is_gui_quit = true;
}

