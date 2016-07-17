#include <QtGui/QOpenGLFramebufferObject>
#include <QtQuick/QQuickWindow>
#include <qsgsimpletexturenode.h>
#include "headers/fb_obj.h"
#include "headers/logorenderer.h"

QQuickFramebufferObject::Renderer* Fb_obj::createRenderer() const
{
  qDebug()<<"createRenderer()";
  return new Fbo_renderer();
}

void Fb_obj::pressEvent()
{
  qDebug()<<"mouse!";
  update();
}

Fbo_renderer::Fbo_renderer()
{
  logo.initialize();
  update();
}

void Fbo_renderer::render()
{
  qDebug()<<"render()";
  logo.render();
  update();
}

QOpenGLFramebufferObject* Fbo_renderer::createFramebufferObject(const QSize &size)
{
  QOpenGLFramebufferObjectFormat format;
  format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
  format.setSamples(4);
  return new QOpenGLFramebufferObject(size, format);
}
