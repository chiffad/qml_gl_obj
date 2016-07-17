#ifndef FBOINSGRENDERER_H
#define FBOINSGRENDERER_H

#include <QtQuick/QQuickFramebufferObject>
#include "headers/logorenderer.h"

class Fbo_obj : public QQuickFramebufferObject
{
  Q_OBJECT
public:
  Renderer *createRenderer() const;

  Q_INVOKABLE void pressEvent();
};
#endif
