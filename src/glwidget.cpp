#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QMouseEvent>

#include "headers/glwidget.h"

Cubes::Cubes()
    : xRot(0),
      yRot(0),
      zRot(0),
      program(0)
{
  memset(textures, 0, sizeof(textures));
}

Cubes::~Cubes()
{
  for(auto &i : textures)
    delete i;

  delete program;
}

void Cubes::rotateBy(int xAngle, int yAngle, int zAngle)
{
  xRot += xAngle;
  yRot += yAngle;
  zRot += zAngle;
  //update();
}

void Cubes::initializeGL()
{
  initializeOpenGLFunctions();

  makeObject();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1

  QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, program);
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

  QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, program);
  const char *fsrc =
      "uniform sampler2D texture;\n"
      "varying mediump vec4 texc;\n"
      "void main(void)\n"
      "{\n"
      "    gl_FragColor = texture2D(texture, texc.st);\n"
      "}\n";
  fshader->compileSourceCode(fsrc);

  program = new QOpenGLShaderProgram;
  program->addShader(vshader);
  program->addShader(fshader);
  program->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
  program->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
  program->link();

  program->bind();
  program->setUniformValue("texture", 0);
}

void Cubes::paintGL()
{
  glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QMatrix4x4 m;
  m.ortho(-0.5f, +0.5f, +0.5f, -0.5f, 4.0f, 15.0f);
  m.translate(0.0f, 0.0f, -10.0f);
  m.rotate(xRot / 16.0f, 1.0f, 0.0f, 0.0f);
  m.rotate(yRot / 16.0f, 0.0f, 1.0f, 0.0f);
  m.rotate(zRot / 16.0f, 0.0f, 0.0f, 1.0f);

  program->setUniformValue("matrix", m);
  program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
  program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
  program->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
  program->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));

  for(int i = 0; i < 6; ++i)
  {
    textures[i]->bind();
    glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
  }
}

void Cubes::makeObject()
{
  const int SIDES = 6;
  const int VERTEX = 4;
  const int COORD = 3;

  static const int coords[SIDES][VERTEX][COORD] = {
     { { +1, -1, -1 }, { -1, -1, -1 }, { -1, +1, -1 }, { +1, +1, -1 } },
     { { +1, +1, -1 }, { -1, +1, -1 }, { -1, +1, +1 }, { +1, +1, +1 } },
     { { +1, -1, +1 }, { +1, -1, -1 }, { +1, +1, -1 }, { +1, +1, +1 } },
     { { -1, -1, -1 }, { -1, -1, +1 }, { -1, +1, +1 }, { -1, +1, -1 } },
     { { +1, -1, +1 }, { -1, -1, +1 }, { -1, -1, -1 }, { +1, -1, -1 } },
     { { -1, -1, +1 }, { +1, -1, +1 }, { +1, +1, +1 }, { -1, +1, +1 } }
  };

  for (int j = 0; j < SIDES; ++j)
     textures[j] = new QOpenGLTexture(QImage(QString(":/images/side%1.png").arg(j + 1)).mirrored());

  QVector<GLfloat> vertData;
  for(int i = 0; i < SIDES; ++i)
    for (int j = 0; j < VERTEX; ++j)
    {
      // vertex position
      vertData.append(0.2 * coords[i][j][0]);
      vertData.append(0.2 * coords[i][j][1]);
      vertData.append(0.2 * coords[i][j][2]);
      // texture coordinate
      vertData.append(j == 0 || j == 3);
      vertData.append(j == 0 || j == 1);
     }
}
