#ifndef RENDERER_H
#define RENDERER_H

#include "tile.h"
#include <QPainter>
#include <QPaintEvent>

class TileManager;
class Renderer
{
public:
    Renderer();
    void SetTileManager(TileManager *inputManager);

    void paint(QPainter *painter, QPaintEvent *event, int elapsed);
    void SetSize(int xres, int yres)
    {
        m_xres=xres;
        m_yres = yres;
    }
private:
    QBrush m_background;
    QBrush m_tileBrush;
    QFont m_textFont;
    QPen m_tilePen;
    QPen m_textPen;
    QColor m_color;
    int m_xres;
    int m_yres;
    TileManager *m_tileManager;
};

#endif // RENDERER_H
