#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram);
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

public:
  explicit GLWidget(QWidget *parent = 0);
  ~GLWidget();

  QSize minimumSizeHint() const Q_DECL_OVERRIDE;
  QSize sizeHint() const Q_DECL_OVERRIDE;
  void rotateBy(int xAngle, int yAngle, int zAngle);
  void setClearColor(const QColor &color);

protected:
  void initializeGL() Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
  void resizeGL(int width, int height) Q_DECL_OVERRIDE;
  void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
  void makeObject();

private:
  QColor clearColor;
  QPoint lastPos;
  int xRot;
  int yRot;
  int zRot;
  QOpenGLTexture *textures[6];
  QOpenGLShaderProgram *program;
  QOpenGLBuffer vbo;
};

#endif
