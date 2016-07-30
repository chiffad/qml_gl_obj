#include <QPainter>
#include <QPaintEngine>
#include <cmath>
#include <QGLWidget>
#include <QOpenGLTexture>
#include <QImage>
#include <QString>
#include "headers/cube_renderer.h"


Cube_renderer::Cube_renderer() : m_board_texture(new QOpenGLTexture(QImage("/home/chiffa/prj/qml_gl_obj/res/board.png"))),
                                 m_program(new QOpenGLShaderProgram), m_x_angle(-35), m_y_angle(2), m_z_angle(0),
                                 m_scale_vect(1,1,1), m_VERTEX_ATTRIBUTE(0), m_TEXCOORD_ATTRIBUTE(1)
{
  qDebug()<<"Cube_renderer()";
}

Cube_renderer::~Cube_renderer()
{
  qDebug()<<"~Cube_renderer()";
  delete m_board_texture;
  delete m_program;
}

void Cube_renderer::initialize()
{
  qDebug()<<"initialize()";

  initializeOpenGLFunctions();
  //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, m_program);
  const char *vsrc =
      "attribute highp vec4 vertex;\n"
      "attribute mediump vec4 texCoord;\n"
      "varying mediump vec4 texc;\n"
      "uniform mediump mat4 matrix;\n"
      "void main(void)\n"
      "{\n"
      "    gl_Position = matrix * vertex;\n"
      "    texc = texCoord;\n"
      "}\n";
  vshader->compileSourceCode(vsrc);

  QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, m_program);
  const char *fsrc =
      "uniform sampler2D texture;\n"
      "varying mediump vec4 texc;\n"
      "void main(void)\n"
      "{\n"
      "    gl_FragColor = texture2D(texture, texc.st);\n"
      "}\n";
  fshader->compileSourceCode(fsrc);

  m_program->addShader(vshader);
  m_program->addShader(fshader);
  m_program->bindAttributeLocation("vertex", m_VERTEX_ATTRIBUTE);
  m_program->bindAttributeLocation("texCoord", m_TEXCOORD_ATTRIBUTE);
  m_program->link();
  m_program->bind();
  m_program->setUniformValue("texture", 0);

  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  create_geometry();
  qDebug()<<"initialize()";
}

void Cube_renderer::set_cube_updates(const QVector3D scale_vect)
{
  qDebug()<<"set_cube_updates";
  m_scale_vect = scale_vect;
  update_modelview();
  render();
  qDebug()<<"set_cube_updates";
}

void Cube_renderer::update_modelview()
{
  qDebug()<<"update_modelview()";
  modelview.rotate(m_x_angle, 1.0f, 0.0f, 0.0f);
  modelview.rotate(m_y_angle, 0.0f, 1.0f, 0.0f);
  modelview.rotate(m_z_angle, 0.0f, 0.0f, 1.0f);
  modelview.scale(m_scale_vect);
  modelview.translate(0.0f, 0.0f, 0.0f);
  qDebug()<<"update_modelview()";
}

void Cube_renderer::render()
{
  qDebug()<<"render()";
  glDepthMask(true);

  //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QMatrix4x4 m;
  m.ortho(-0.5f, +0.5f, +0.5f, -0.5f, 4.0f, 15.0f);
  m.translate(0.0f, 0.0f, -10.0f);
  m.rotate(-35.0f, 1.0f, 0.0f, 0.0f);
  m.rotate(2.0f, 0.0f, 1.0f, 0.0f);
  //m.rotate(zRot / 16.0f, 0.0f, 0.0f, 1.0f);
  initializeOpenGLFunctions();

  m_program->setUniformValue("matrix", m);
  m_program->enableAttributeArray(m_VERTEX_ATTRIBUTE);
  m_program->enableAttributeArray(m_TEXCOORD_ATTRIBUTE);
  m_program->setAttributeBuffer(m_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
  m_program->setAttributeBuffer(m_TEXCOORD_ATTRIBUTE, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));

  m_board_texture->bind();

  for(int i = 0; i < SIDES; ++i)
    glDrawArrays(GL_TRIANGLE_FAN, i * VERTEX, VERTEX);

  m_x_angle += 1.0f;
  m_y_angle += 1.0f;
  m_z_angle += 1.0f;
  qDebug()<<"render()";
}

void Cube_renderer::create_geometry()
{
  qDebug()<<"create_geometry()";
  static const int coords[SIDES][VERTEX][VERT_COORD] = {
      { { +1, -1, -1 }, { -1, -1, -1 }, { -1, +1, -1 }, { +1, +1, -1 } },
      { { +1, +1, -1 }, { -1, +1, -1 }, { -1, +1, +1 }, { +1, +1, +1 } },
      { { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }, { +1, +1, +1 } },
      { { -1, -1, -1 }, { -1, -1, +1 }, { -1, +1, +1 }, { -1, +1, -1 } },
      { { +1, -1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { +1, -1, -1 } },
      { { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } }
  };

  QVector<GLfloat> vertData;
  for(int i = 0; i < SIDES; ++i)
    for(int j = 0; j < VERTEX; ++j)
    {
      // vertex position
      vertData.append(0.2 * coords[i][j][0]);
      vertData.append(0.2 * coords[i][j][1]);
      vertData.append(0.2 * coords[i][j][2]);
      // texture coordinate
      vertData.append(j == 0 || j == 3);
      vertData.append(j == 0 || j == 1);
    }

  m_buffer.create();
  m_buffer.bind();
  m_buffer.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
  qDebug()<<"create_geometry()";
}
