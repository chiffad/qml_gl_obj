#ifndef CUBERENDERER_H
#define CUBERENDERER_H

#include <QtGui/qvector3d.h>
#include <QtGui/qmatrix4x4.h>
#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglfunctions.h>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>

#include <QTime>
#include <QVector>

class Cube_renderer : protected QOpenGLFunctions
{
public:
  explicit Cube_renderer();
  ~Cube_renderer();
  void render();
  void initialize();
  void set_cube_updates(const QVector3D scale_vect);
  //void set_angle(const double x_angle, const double y_angle, const double z_angle);

private:
  void create_geometry();
  void update_modelview();

private:
   enum CUBE_CHARACteRS{VERT_COORD = 3, VERTEX = 4, SIDES = 6};

private:
  QVector<QOpenGLTexture*> m_board_texture;
  QOpenGLShaderProgram *m_program;

  QMatrix4x4 modelview;
  QOpenGLBuffer m_buffer;

  float m_x_angle;
  float m_y_angle;
  float m_z_angle;
  QVector3D m_scale_vect;

  const int m_VERTEX_ATTRIBUTE;
  const int m_TEXCOORD_ATTRIBUTE;
};
#endif
