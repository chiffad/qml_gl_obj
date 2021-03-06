#ifndef CUBERENDERER_H
#define CUBERENDERER_H

#include <QtGui/qvector3d.h>
#include <QtGui/qmatrix4x4.h>
#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglfunctions.h>

#include <QTime>
#include <QVector>

class Cube_renderer : protected QOpenGLFunctions
{
public:
  Cube_renderer();
  ~Cube_renderer();
  void render();
  void initialize();
  void scale(const double sc);
  //void set_angle(const double x_angle, const double y_angle, const double z_angle);

private:
  void paint();
  void createGeometry();

private:
  QOpenGLShaderProgram m_program;
  QVector<QVector3D> m_vertices;
  QVector<QVector3D> m_normals;
  double m_angle;
//  double m_x_angle;
//  double m_y_angle;
//  double m_z_angle;
  double m_scale;
  int m_vertexAttr;
  int m_normalAttr;
  int m_matrixUniform;
};
#endif
