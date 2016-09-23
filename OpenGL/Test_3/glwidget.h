#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include "transform3d.h"

//QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
//QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

class GLWidget: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent);
    ~GLWidget();
    void printVersionInformation();
    struct Vertex
    {
        Q_DECL_CONSTEXPR Vertex(const QVector3D &position, const QVector3D &color):
             m_position(position), m_color(color){}
        static Q_DECL_CONSTEXPR int positionOffset() { return offsetof(Vertex, m_position); }
        static Q_DECL_CONSTEXPR int colorOffset() { return offsetof(Vertex, m_color); }
        static Q_DECL_CONSTEXPR int stride() { return sizeof(Vertex); }

        QVector3D m_position;
        QVector3D m_color;
        static const int PositionTupleSize = 3;
        static const int ColorTupleSize = 3;
    };

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void makeObject();

protected slots:
  void update();

private:
    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject object;
    Transform3D transform;
    QMatrix4x4 projection;
    GLint modelToWorld;
    GLint worldToView;


};

#endif // GLWIDGET_H
