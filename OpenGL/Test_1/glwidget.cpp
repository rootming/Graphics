#include "glwidget.h"
#include <QOpenGLShader>

static const GLWidget::Vertex sg_vertexes[] = {
  GLWidget::Vertex( QVector3D( -0.75f,  -0.75f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f) ),
  GLWidget::Vertex( QVector3D(0.75f, -0.75f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f) ),
  GLWidget::Vertex( QVector3D( 0.00f, 0.75f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f) )
};


GLWidget::GLWidget(QWidget *parent):
    QOpenGLWidget(parent)
{

}

GLWidget::~GLWidget()
{

}


void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    printVersionInformation();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    makeObject();
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1

    QOpenGLShader vshader(QOpenGLShader::Vertex, this);
    QOpenGLShader fshader(QOpenGLShader::Fragment, this);

    if(!vshader.compileSourceFile(":/shader/vertex.vert")){
        qDebug()<< "Vertex Shader compile fail";
    }
    if(!fshader.compileSourceFile(":/shader/frag.frag")){
        qDebug()<< "Fragment Shader compile fail";
    }
    program.addShader(&vshader);
    program.addShader(&fshader);

    program.link();
    program.bind();
    object.create();
    object.bind();

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.allocate(sg_vertexes, sizeof(sg_vertexes));

    program.enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    program.enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    program.setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, Vertex::positionOffset(),  Vertex::PositionTupleSize,  Vertex::stride());
    program.setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT,  Vertex::colorOffset(),  Vertex::ColorTupleSize, Vertex::stride());;

    object.release();
    vbo.release();
    program.release();

}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    program.bind();
    object.bind();
    glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
    object.release();
    program.release();
}

void GLWidget::makeObject()
{



}

void GLWidget::resizeGL(int w, int h)
{
    qDebug() << w << h << endl;
}

void GLWidget::printVersionInformation()
{
  QString glType;
  QString glVersion;
  QString glProfile;

  // Get Version Information
  glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
  glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

  // Get Profile Information
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
  switch (format().profile())
  {
    CASE(NoProfile);
    CASE(CoreProfile);
    CASE(CompatibilityProfile);
  }
#undef CASE

  // qPrintable() will print our QString w/o quotes around it.
  qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}
