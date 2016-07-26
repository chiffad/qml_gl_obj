#ifndef FBOGRENDERER_H
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
  Renderer* createRenderer() const Q_DECL_OVERRIDE;

  Q_PROPERTY(QString fig_type READ get_fig_type WRITE set_fig_type)
  QString get_fig_type() const;
  void set_fig_type(const QString &name);

  Q_INVOKABLE void pressEvent();

public:
  double get_scale() const;

private:
  float m_scale;
  QString m_fig_type;
};


class Fbo_renderer : public QQuickFramebufferObject::Renderer
{
public:
  Fbo_renderer();
  ~Fbo_renderer();
  QOpenGLFramebufferObject* createFramebufferObject(const QSize &size) Q_DECL_OVERRIDE;
  void synchronize(QQuickFramebufferObject *item) Q_DECL_OVERRIDE;
  void render() Q_DECL_OVERRIDE;
  void update_cube();
  void scale_cube_on_vect();

private:
  Cube_renderer *cube;
  float m_scale;
  QString m_fig_type;
};
#endif
