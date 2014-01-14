#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QBrush>
#include <QPen>

class Renderer;

class canvas : public QWidget
{
    Q_OBJECT
public:
    explicit canvas(Renderer *myRenderer, QWidget *parent = 0);
    //bool saveImage(const QString &file);
    //bool loadImage(const QString &file);
    void initPixmap();
protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
    void draw();

private:
    QImage *m_image;
    QPixmap m_pixmap;
    Renderer *m_renderer;
    QBrush m_myBrush;
    QPen m_myPen;
};

#endif // CANVAS_H
