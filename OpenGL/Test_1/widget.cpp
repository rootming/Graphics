#include "widget.h"
#include <QGridLayout>
#include <QSurfaceFormat>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout layout(parent);
    mygl = new GLWidget(parent);
    layout.addWidget(mygl);
    setLayout(&layout);
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3, 3);
    mygl->setFormat(format);

}

Widget::~Widget()
{

}
