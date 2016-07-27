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
  void set_cube_updates(const QVector3D scale_vect);
  //void set_angle(const double x_angle, const double y_angle, const double z_angle);

private:
  void paint();
  void create_geometry();
  void update_modelview();
  void generate_texture();

private:
  QOpenGLShaderProgram m_program;
  GLuint textures[1];
  QVector<QVector3D> m_vertices;
  QVector<QVector3D> m_normals;
  QMatrix4x4 modelview;
  float m_x_angle;
  float m_y_angle;
  float m_z_angle;
  QVector3D m_scale_vect;
  int m_vertexAttr;
  int m_normalAttr;
  int m_matrixUniform;
};
#endif
