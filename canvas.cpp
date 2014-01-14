#include "canvas.h"
#include "renderer.h"
#include <QPainter>
#include <iostream>

canvas::canvas(Renderer *myRenderer, QWidget *parent) :
    QWidget(parent), m_renderer(myRenderer)
{
    //setFixedSize(400,400);
}

void canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    int elapsed = 0;// XXX unused
    m_renderer->paint(&painter, event, elapsed);
    painter.end();
}

void canvas::draw()
{
    this->repaint();
    std::cout << "canvas: draw()" << std::endl;
}
