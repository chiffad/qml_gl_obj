#include <QPainter>
#include <QPaintEngine>
#include <math.h>
#include "headers/logorenderer.h"

LogoRenderer::LogoRenderer()
{
}

LogoRenderer::~LogoRenderer()
{
}


void LogoRenderer::paintQtLogo()
{
  program.enableAttributeArray(normalAttr);
  program.enableAttributeArray(vertexAttr);

  program.setAttributeArray(vertexAttr, vertices.constData());
  program.setAttributeArray(normalAttr, normals.constData());
  glDrawArrays(GL_QUADS, 0, vertices.size());

  program.disableAttributeArray(normalAttr);
  program.disableAttributeArray(vertexAttr);
}


void LogoRenderer::initialize()
{
  initializeOpenGLFunctions();

  glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

  QOpenGLShader *vshader1 = new QOpenGLShader(QOpenGLShader::Vertex, &program);
  const char *vsrc1 =
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
  vshader1->compileSourceCode(vsrc1);

  QOpenGLShader *fshader1 = new QOpenGLShader(QOpenGLShader::Fragment, &program);
  const char *fsrc1 =
    "varying mediump vec4 color;\n"
    "void main(void)\n"
    "{\n"
    "    gl_FragColor = color;\n"
    "}\n";
  fshader1->compileSourceCode(fsrc1);

  program.addShader(vshader1);
  program.addShader(fshader1);
  program.link();

  vertexAttr = program.attributeLocation("vertex");
  normalAttr = program.attributeLocation("normal");
  matrixUniform1 = program.uniformLocation("matrix");

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  m_fAngle = 0;
  m_fScale = 1;
  createGeometry();
}

void LogoRenderer::render()
{
    qDebug()<<"render";
  glDepthMask(true);

  glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  glFrontFace(GL_CW);
  glCullFace(GL_FRONT);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  QMatrix4x4 modelview;
  modelview.rotate(m_fAngle, 0.0f, 1.0f, 0.0f);
  modelview.rotate(m_fAngle, 1.0f, 0.0f, 0.0f);
  modelview.rotate(m_fAngle, 0.0f, 0.0f, 1.0f);
  modelview.scale(m_fScale);
  modelview.translate(0.0f, -0.2f, 0.0f);

  program.bind();
  program.setUniformValue(matrixUniform1, modelview);
  paintQtLogo();
  program.release();
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  m_fAngle += 1.0f;
}

void LogoRenderer::createGeometry()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  qDebug()<<"createGeometry";
  vertices.clear();
 // normals.clear();

  const QVector3D v1 = QVector3D(+1.0f, +1.0f, +1.0f);
  const QVector3D v2 = QVector3D(+1.0f, +1.0f, -1.0f);
  const QVector3D v3 = QVector3D(+1.0f, -1.0f, +1.0f);
  const QVector3D v4 = QVector3D(+1.0f, -1.0f, -1.0f);

  const QVector3D v5 = QVector3D(-1.0f, +1.0f, +1.0f);
  const QVector3D v6 = QVector3D(-1.0f, +1.0f, -1.0f);
  const QVector3D v7 = QVector3D(-1.0f, -1.0f, +1.0f);
  const QVector3D v8 = QVector3D(-1.0f, -1.0f, -1.0f);

  normals.append(QVector3D(0,1,0));
  vertices.append(v1);
  vertices.append(v2);
  vertices.append(v5);
  vertices.append(v6);

  normals.append(QVector3D(1,0,0));
  vertices.append(v4);
  vertices.append(v2);
  vertices.append(v3);
  vertices.append(v1);

  normals.append(QVector3D(0,0,-1));
  vertices.append(v4);
  vertices.append(v2);
  vertices.append(v8);
  vertices.append(v6);

  normals.append(QVector3D(0,-1,0));
  vertices.append(v3);
  vertices.append(v4);
  vertices.append(v7);
  vertices.append(v8);

  normals.append(QVector3D(-1,0,0));
  vertices.append(v8);
  vertices.append(v6);
  vertices.append(v7);
  vertices.append(v5);

  normals.append(QVector3D(0,0,+1));
  vertices.append(v3);
  vertices.append(v1);
  vertices.append(v7);
  vertices.append(v5);

  /*vertices.append(v8);
  vertices.append(v7);
  vertices.append(v5);//Left

  vertices.append(v8);
  vertices.append(v5);
  vertices.append(v6);//Left

  vertices.append(v2);
  vertices.append(v8);
  vertices.append(v6);//Bottom

  vertices.append(v3);
  vertices.append(v7);
  vertices.append(v8);//Bottom

  vertices.append(v2);
  vertices.append(v4);
  vertices.append(v8);//Back

  vertices.append(v2);
  vertices.append(v8);
  vertices.append(v6);//Back

  vertices.append(v5);
  vertices.append(v7);
  vertices.append(v3);//Front

  vertices.append(v1);
  vertices.append(v5);
  vertices.append(v3);//Front

  vertices.append(v1);
  vertices.append(v4);
  vertices.append(v2);//Right

  vertices.append(v4);
  vertices.append(v1);
  vertices.append(v3);//Right

  vertices.append(v1);
  vertices.append(v2);
  vertices.append(v6);//Top

  vertices.append(v1);
  vertices.append(v6);
  vertices.append(v5);//Top*/
}
