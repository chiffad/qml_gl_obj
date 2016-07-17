#include <QtGui/QOpenGLFramebufferObject>
#include <QtQuick/QQuickWindow>
#include <qsgsimpletexturenode.h>
#include "headers/fbo_obj.h"
#include "headers/logorenderer.h"

class Fbo_renderer : public QQuickFramebufferObject::Renderer
{
public:
  Fbo_renderer()
  {
    logo.initialize();
    update();
  }

  void render()
  {
    qDebug()<<"render()";
    logo.render();
  //  update();
  }

  QOpenGLFramebufferObject* createFramebufferObject(const QSize &size)
  {
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4);
    return new QOpenGLFramebufferObject(size, format);
  }

private:
  LogoRenderer logo;
};

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
