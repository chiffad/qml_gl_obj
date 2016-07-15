#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QPoint>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram);
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

class Cubes : protected QOpenGLFunctions
{
public:
  explicit Cubes();
  ~Cubes();

  void rotateBy(int xAngle, int yAngle, int zAngle);

protected:
  void initializeGL();
  void paintGL();

private:
  void makeObject();

private:
  int xRot;
  int yRot;
  int zRot;
  QOpenGLTexture *textures[6];
  QOpenGLShaderProgram *program;
};

#endif
