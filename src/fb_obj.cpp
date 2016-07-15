#include <QtGui/QOpenGLFramebufferObject>
#include <QtQuick/QQuickWindow>
#include <qsgsimpletexturenode.h>
#include "headers/fb_obj.h"
#include "headers/cubes.h"

QQuickFramebufferObject::Renderer* Fbo_obj::createRenderer() const
{
  qDebug()<<"createRenderer()";
  return new Fbo_renderer();
}

void Fbo_obj::pressEvent()
{
  qDebug()<<"mouse!";
  update();
}

Fbo_renderer::Fbo_renderer()
{
  cubes.initialize();
  update();
}

void Fbo_renderer::render()
{
  qDebug()<<"render()";
  cubes.paint();
//  update();
}

QOpenGLFramebufferObject* Fbo_renderer::createFramebufferObject(const QSize &size)
{
  QOpenGLFramebufferObjectFormat format;
  format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
  format.setSamples(4);
  return new QOpenGLFramebufferObject(size, format);
}
