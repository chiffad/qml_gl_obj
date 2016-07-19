#include <QtGui/QOpenGLFramebufferObject>
#include <QtQuick/QQuickWindow>
#include <qsgsimpletexturenode.h>
#include "headers/fb_obj.h"
#include "headers/logorenderer.h"

Fb_obj::~Fb_obj()
{
}

QQuickFramebufferObject::Renderer* Fb_obj::createRenderer() const
{
  qDebug()<<"createRenderer()";
  renderer = new Fbo_renderer();
  return renderer;
}

void Fb_obj::pressEvent()
{
  renderer->scale(0.4f);
  update();
}

Fbo_renderer::Fbo_renderer()
{
  logo.initialize();
  update();
}

QOpenGLFramebufferObject* Fbo_renderer::createFramebufferObject(const QSize &size)
{
  QOpenGLFramebufferObjectFormat format;
  format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
  format.setSamples(4);
  return new QOpenGLFramebufferObject(size, format);
}

void Fbo_renderer::render()
{
  logo.render();
  update();
}

void Fbo_renderer::scale(const double sc)
{
  logo.scale(sc);
}
