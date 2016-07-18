#ifndef LOGORENDERER_H
#define LOGORENDERER_H

#include <QtGui/qvector3d.h>
#include <QtGui/qmatrix4x4.h>
#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglfunctions.h>

#include <QTime>
#include <QVector>

class LogoRenderer : protected QOpenGLFunctions
{
public:
  LogoRenderer();
  ~LogoRenderer();
  void render();
  void initialize();

private:
  void paint();
  void createGeometry();

private:
  QOpenGLShaderProgram program;
  QVector<QVector3D> vertices;
  QVector<QVector3D> normals;
  qreal m_fAngle;
  qreal m_fScale;
  int vertexAttr;
  int normalAttr;
  int matrixUniform1;
};
#endif
