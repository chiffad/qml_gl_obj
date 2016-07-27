#include <QPainter>
#include <QPaintEngine>
#include <cmath>
#include <QGLWidget>
#include "headers/cube_renderer.h"

Cube_renderer::Cube_renderer() : m_x_angle(-35), m_y_angle(10), m_z_angle(0), m_scale_vect(1,1,1),
                                 m_vertexAttr(0), m_normalAttr(0), m_matrixUniform(0)
{
}

Cube_renderer::~Cube_renderer()
{
}

void Cube_renderer::paint()
{
  m_program.enableAttributeArray(m_normalAttr);
  m_program.enableAttributeArray(m_vertexAttr);

  m_program.setAttributeArray(m_vertexAttr, m_vertices.constData());
  m_program.setAttributeArray(m_normalAttr, m_normals.constData());

  glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());

  m_program.disableAttributeArray(m_normalAttr);
  m_program.disableAttributeArray(m_vertexAttr);
}

void Cube_renderer::initialize()
{
  initializeOpenGLFunctions();

  //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, &m_program);
  const char *vsrc =
    "attribute highp vec4 vertex;\n"
    "attribute mediump vec3 normal;\n"
    "uniform mediump mat4 matrix;\n"
    "varying mediump vec4 color;\n"
    "void main(void)\n"
    "{\n"
    "    vec3 toLight = normalize(vec3(0.0, 0.3, 1.0));\n"
    "    float angle = max(dot(normal, toLight), 0.0);\n"
    "    vec3 col = vec3(0.40, 1.0, 0.0);\n"
    "    color = vec4(col * 0.2 + col * 0.8 * angle, 1.0);\n"
    "    color = clamp(color, 0.0, 1.0);\n"
    "    gl_Position = matrix * vertex;\n"
    "}\n";
  vshader->compileSourceCode(vsrc);

  QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, &m_program);
  const char *fsrc =
    "varying mediump vec4 color;\n"
    "void main(void)\n"
    "{\n"
    "    gl_FragColor = color;\n"
    "}\n";
  fshader->compileSourceCode(fsrc);

  m_program.addShader(vshader);
  m_program.addShader(fshader);
  m_program.link();

  m_vertexAttr = m_program.attributeLocation("vertex");
  m_normalAttr = m_program.attributeLocation("normal");
  m_matrixUniform = m_program.uniformLocation("matrix");

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  glEnable(GL_TEXTURE_2D);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  generate_texture();

  create_geometry();
}

void Cube_renderer::set_cube_updates(const QVector3D scale_vect)
{
  m_scale_vect = scale_vect;
  update_modelview();
  render();
}

void Cube_renderer::update_modelview()
{
  modelview.rotate(m_x_angle, 1.0f, 0.0f, 0.0f);
  modelview.rotate(m_y_angle, 0.0f, 1.0f, 0.0f);
  modelview.rotate(m_z_angle, 0.0f, 0.0f, 1.0f);
  modelview.scale(m_scale_vect);
  modelview.translate(0.0f, 0.0f, 0.0f);
}

void Cube_renderer::render()
{
  glDepthMask(true);

  //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );//?
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  glFrontFace(GL_CW);
  glCullFace(GL_FRONT);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  m_program.bind();
  m_program.setUniformValue(m_matrixUniform, modelview);
 // update_modelview();
  paint();
  m_program.release();
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  m_x_angle += 1.0f;
  m_y_angle += 1.0f;
  m_z_angle += 1.0f;
}

void Cube_renderer::generate_texture()
{
  glGenTextures(1, textures);

  QImage boardIm;
  boardIm.load("res/board.png");
  boardIm = QGLWidget::convertToGLFormat(boardIm);
  glBindTexture(GL_TEXTURE_2D, textures[0]);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)boardIm.width(), (GLsizei)boardIm.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, boardIm.bits());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Cube_renderer::create_geometry()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  m_vertices.clear();
  m_normals.clear();

  const float MAX_SIZE = 0.5;
  const QVector3D v1 = QVector3D(+MAX_SIZE, +MAX_SIZE, +MAX_SIZE);
  const QVector3D v2 = QVector3D(+MAX_SIZE, +MAX_SIZE, -MAX_SIZE);
  const QVector3D v3 = QVector3D(+MAX_SIZE, -MAX_SIZE, +MAX_SIZE);
  const QVector3D v4 = QVector3D(+MAX_SIZE, -MAX_SIZE, -MAX_SIZE);

  const QVector3D v5 = QVector3D(-MAX_SIZE, +MAX_SIZE, +MAX_SIZE);
  const QVector3D v6 = QVector3D(-MAX_SIZE, +MAX_SIZE, -MAX_SIZE);
  const QVector3D v7 = QVector3D(-MAX_SIZE, -MAX_SIZE, +MAX_SIZE);
  const QVector3D v8 = QVector3D(-MAX_SIZE, -MAX_SIZE, -MAX_SIZE);

  for(int i = 0; i<3; ++i)
    m_normals.append(QVector3D(-1,0,0));
  m_vertices.append(v8);
  m_vertices.append(v7);
  m_vertices.append(v5);//Back

  for(int i = 0; i<3; ++i)
    m_normals.append(QVector3D(-1,0,0));
  m_vertices.append(v8);
  m_vertices.append(v5);
  m_vertices.append(v6);//Back

  for(int i = 0; i<3; ++i)
    m_normals.append(QVector3D(0,0,-1));
  m_vertices.append(v2);
  m_vertices.append(v8);
  m_vertices.append(v6);//Bottom

  for(int i = 0; i<3; ++i)
    m_normals.append(QVector3D(0,0,-1));
  m_vertices.append(v2);
  m_vertices.append(v4);
  m_vertices.append(v8);//Bottom

  for(int i = 0; i<3; ++i)
    m_normals.append(QVector3D(0,-1,0));
  m_vertices.append(v3);
  m_vertices.append(v7);
  m_vertices.append(v8);//Left

  for(int i = 0; i<3; ++i)
    m_normals.append(QVector3D(0,-1,0));
  m_vertices.append(v3);//Left
  m_vertices.append(v8);
  m_vertices.append(v4);

  for(int i = 0; i<3; ++i)
    m_normals.append(QVector3D(0,0,1));
  m_vertices.append(v5);//Top
  m_vertices.append(v7);
  m_vertices.append(v3);

  for(int i = 0; i<3; ++i)
    m_normals.append(QVector3D(0,0,1));
  m_vertices.append(v1);//Top
  m_vertices.append(v5);
  m_vertices.append(v3);

  for(int i = 0; i<3; ++i)
    m_normals.append(QVector3D(1,0,0));
  m_vertices.append(v1);//Fase
  m_vertices.append(v4);
  m_vertices.append(v2);

  for(int i = 0; i<3; ++i)
    m_normals.append(QVector3D(1,0,0));
  m_vertices.append(v4);//Fase
  m_vertices.append(v1);
  m_vertices.append(v3);

  for(int i = 0; i<3; ++i)
    m_normals.append(QVector3D(0,1,0));
  m_vertices.append(v1);//Right
  m_vertices.append(v2);
  m_vertices.append(v6);

  for(int i = 0; i<3; ++i)
    m_normals.append(QVector3D(0,1,0));
  m_vertices.append(v1);//Right
  m_vertices.append(v6);
  m_vertices.append(v5);

  glBindTexture(GL_TEXTURE_2D, textures[0]);

  GLfloat cubeTextureArray[4][2];

  cubeTextureArray[0][0] = 0.0;
  cubeTextureArray[0][1] = 0.0;

  cubeTextureArray[1][0] = 1.0;
  cubeTextureArray[1][1] = 0.0;

  cubeTextureArray[2][0] = 1.0;
  cubeTextureArray[2][1] = 1.0;

  cubeTextureArray[3][0] = 0.0;
  cubeTextureArray[3][1] = 1.0;

  GLubyte cubeIndexArray[4];

  cubeIndexArray[0] = 0;
  cubeIndexArray[1] = 3;
  cubeIndexArray[2] = 2;
  cubeIndexArray[3] = 1;

  //glVertexPointer(3, GL_FLOAT, 0, m_vertices);
  glTexCoordPointer(2, GL_FLOAT, 0, cubeTextureArray);
  glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cubeIndexArray);
}
