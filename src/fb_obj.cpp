#include <QtGui/QOpenGLFramebufferObject>
#include <QtQuick/QQuickWindow>
#include <qsgsimpletexturenode.h>
#include "headers/fb_obj.h"
#include "headers/cube_renderer.h"

Fb_obj::Fb_obj() : m_scale(1)
{
}

Fb_obj::~Fb_obj()
{
}

QQuickFramebufferObject::Renderer* Fb_obj::createRenderer() const
{
  return new Fbo_renderer();
}

void Fb_obj::pressEvent()
{
  m_scale = 0.2;
  update();
}

double Fb_obj::get_scale() const
{
  return m_scale;
}

//======================================================

Fbo_renderer::Fbo_renderer() : cube(new Cube_renderer()), m_scale(1)
{
  cube->initialize();
  update();
}

Fbo_renderer::~Fbo_renderer()
{
  delete cube;
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
  cube->render();
  update();
}

void Fbo_renderer::synchronize(QQuickFramebufferObject *item)
{
  qDebug()<<"synchronize";
  Fb_obj *fbitem = static_cast<Fb_obj *>(item);
  m_scale = fbitem->get_scale();
  scale_cube();
}

void Fbo_renderer::scale_cube()
{
  cube->scale(m_scale);
  //m_scale = 1;
}
