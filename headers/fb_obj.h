#ifndef FBORENDERER_H
#define FBORENDERER_H

#include <QtQuick/QQuickFramebufferObject>
#include "headers/cube_renderer.h"

class Fbo_renderer;

class Fb_obj : public QQuickFramebufferObject
{
  Q_OBJECT
public:
  Fb_obj();
  ~Fb_obj();
  Renderer *createRenderer() const Q_DECL_OVERRIDE;

  Q_INVOKABLE void pressEvent();

  double get_scale() const;

private:
  double m_scale;
};

class Fbo_renderer : public QQuickFramebufferObject::Renderer
{
public:
  Fbo_renderer();
  ~Fbo_renderer();
  QOpenGLFramebufferObject* createFramebufferObject(const QSize &size) Q_DECL_OVERRIDE;
  void render() Q_DECL_OVERRIDE;
  void synchronize(QQuickFramebufferObject *item) Q_DECL_OVERRIDE;
  void scale_cube();

private:
  Cube_renderer *cube;
  double m_scale;
};
#endif
