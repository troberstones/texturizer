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

private:
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;

    TileManager *m_tileManager;
};

#endif // RENDERER_H
