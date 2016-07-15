#ifndef FBOINSGRENDERER_H
#define FBOINSGRENDERER_H

#include <QtQuick/QQuickFramebufferObject>
#include "headers/cubes.h"

class Fbo_obj : public QQuickFramebufferObject
{
  Q_OBJECT
public:
  Renderer *createRenderer() const;

  Q_INVOKABLE void pressEvent();
};

class Fbo_renderer : public QQuickFramebufferObject::Renderer
{
public:
  Fbo_renderer();
  void render();
  QOpenGLFramebufferObject* createFramebufferObject(const QSize &size);

private:
  Cubes cubes;
};
#endif
