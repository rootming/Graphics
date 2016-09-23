#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

//QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
//QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

class GLWidget: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent);
    ~GLWidget();
    void printVersionInformation();
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
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
private:
    QOpenGLShaderProgram program;
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject object;

};

#endif // GLWIDGET_H
