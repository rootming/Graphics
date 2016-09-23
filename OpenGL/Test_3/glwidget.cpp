#include "glwidget.h"
#include <QOpenGLShader>

// Front Verticies
#define VERTEX_FTR GLWidget::Vertex( QVector3D( 0.5f,  0.5f,  0.5f), QVector3D( 1.0f, 0.0f, 0.0f ) )
#define VERTEX_FTL GLWidget::Vertex( QVector3D(-0.5f,  0.5f,  0.5f), QVector3D( 0.0f, 1.0f, 0.0f ) )
#define VERTEX_FBL GLWidget::Vertex( QVector3D(-0.5f, -0.5f,  0.5f), QVector3D( 0.0f, 0.0f, 1.0f ) )
#define VERTEX_FBR GLWidget::Vertex( QVector3D( 0.5f, -0.5f,  0.5f), QVector3D( 0.0f, 0.0f, 0.0f ) )

// Back Verticies
#define VERTEX_BTR GLWidget::Vertex( QVector3D( 0.5f,  0.5f, -0.5f), QVector3D( 1.0f, 1.0f, 0.0f ) )
#define VERTEX_BTL GLWidget::Vertex( QVector3D(-0.5f,  0.5f, -0.5f), QVector3D( 0.0f, 1.0f, 1.0f ) )
#define VERTEX_BBL GLWidget::Vertex( QVector3D(-0.5f, -0.5f, -0.5f), QVector3D( 1.0f, 0.0f, 1.0f ) )
#define VERTEX_BBR GLWidget::Vertex( QVector3D( 0.5f, -0.5f, -0.5f), QVector3D( 1.0f, 1.0f, 1.0f ) )

// Create a colored cube
static const GLWidget::Vertex sg_vertexes[] = {
    // Face 1 (Front)
    VERTEX_FTR, VERTEX_FTL, VERTEX_FBL,
    VERTEX_FBL, VERTEX_FBR, VERTEX_FTR,
    // Face 2 (Back)
    VERTEX_BBR, VERTEX_BTL, VERTEX_BTR,
    VERTEX_BTL, VERTEX_BBR, VERTEX_BBL,
    // Face 3 (Top)
    VERTEX_FTR, VERTEX_BTR, VERTEX_BTL,
    VERTEX_BTL, VERTEX_FTL, VERTEX_FTR,
    // Face 4 (Bottom)
    VERTEX_FBR, VERTEX_FBL, VERTEX_BBL,
    VERTEX_BBL, VERTEX_BBR, VERTEX_FBR,
    // Face 5 (Left)
    VERTEX_FBL, VERTEX_FTL, VERTEX_BTL,
    VERTEX_FBL, VERTEX_BTL, VERTEX_BBL,
    // Face 6 (Right)
    VERTEX_FTR, VERTEX_FBR, VERTEX_BBR,
    VERTEX_BBR, VERTEX_BTR, VERTEX_FTR
};

#undef VERTEX_BBR
#undef VERTEX_BBL
#undef VERTEX_BTL
#undef VERTEX_BTR

#undef VERTEX_FBR
#undef VERTEX_FBL
#undef VERTEX_FTL
#undef VERTEX_FTR

GLWidget::GLWidget(QWidget *parent):
    QOpenGLWidget(parent)
{
    transform.translate(0.0f, 0.0f, -5.0f);
}

GLWidget::~GLWidget()
{

}


void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    printVersionInformation();
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    makeObject();
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

    // Cache Uniform Locations
    modelToWorld = program.uniformLocation("modelToWorld");
    worldToView = program.uniformLocation("worldToView");

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.allocate(sg_vertexes, sizeof(sg_vertexes));

    object.create();
    object.bind();

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
    program.setUniformValue(worldToView, projection);
    object.bind();
    program.setUniformValue(modelToWorld, transform.toMatrix());
    glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
    object.release();
    program.release();
}

void GLWidget::update()
{
    // Update instance information
    transform.rotate(1.0f, QVector3D(0.4f, 0.3f, 0.3f));

    // Schedule a redraw
    QOpenGLWidget::update();
}

void GLWidget::makeObject()
{



}


void GLWidget::resizeGL(int w, int h)
{
    projection.setToIdentity();
    projection.perspective(45.0f, w / float(h), 0.0f, 1000.0f);
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
