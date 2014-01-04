#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

class Renderer;

class canvas : public QWidget
{
    Q_OBJECT
public:
    explicit canvas(Renderer *myRenderer, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
    void draw();

private:
    Renderer *m_renderer;
};

#endif // CANVAS_H
