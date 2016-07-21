#ifndef FBOINSGRENDERER_H
#define FBOINSGRENDERER_H

#include <QtQuick/QQuickFramebufferObject>
#include "headers/cube_renderer.h"

class Fbo_renderer;

class Fb_obj : public QQuickFramebufferObject
{
  Q_OBJECT
public:
  ~Fb_obj();
  Renderer *createRenderer() const;

  Q_INVOKABLE void pressEvent();

  mutable Fbo_renderer *renderer;
};

class Fbo_renderer : public QQuickFramebufferObject::Renderer
{
public:
  Fbo_renderer();
  void render();
  QOpenGLFramebufferObject* createFramebufferObject(const QSize &size);
  void scale(const double sc);

private:
  Cube_renderer cube;
};
#endif
