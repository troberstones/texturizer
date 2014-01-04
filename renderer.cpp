#include "renderer.h"
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QWidget>

#include "tilemanager.h"
#include "tile.h"
#include <iostream>

Renderer::Renderer():
    m_tileManager(0)
{
    if(m_tileManager)
        m_tileManager->Prep();

    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

    background = QBrush(QColor(64, 32, 64));
    circleBrush = QBrush(gradient);
    circlePen = QPen(Qt::black);
    circlePen.setWidth(1);
    textPen = QPen(Qt::white);
    textFont.setPixelSize(50);
}

void Renderer::SetTileManager(TileManager *inputManager)
{
   m_tileManager = inputManager;
   m_tileManager->Prep();
}

void Renderer::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{

    painter->fillRect(event->rect(), background);
    if(!m_tileManager)
    {
        std::cout << "Renderer: No Tile Manager!" << std::endl;
        return;
    }

    //painter->translate(100, 100);
#define WIDTH 200
#define HEIGHT 200
    painter->save();
    painter->setBrush(circleBrush);
    painter->setPen(circlePen);

    // Loop over the tiles and draw tiles in the
    // specified positions
    int tileCount = m_tileManager->GetCount();
    if(tileCount > 100000 || tileCount < 0)
    {
        std::cout << "Fishy tile count:" << tileCount << std::endl;
        return;
    }
    std::cout << "tileCount:" << tileCount << std::endl;
    // Get vector instead XXX
    for(int i = 0; i < tileCount; ++i)
    {
       Tile &tile = m_tileManager->GetTile(i);
       size_t splatCount = tile.GetCount();
       Tile::ItemArray &curItems = tile.GetItemArray();
       if(curItems.size() < splatCount)
       {
           std::cout << "[renderer.cpp] ItemArray size mismatch. Clamping" << std::endl;
           splatCount = curItems.size();
       }
       for(size_t j = 0; j < splatCount; ++j)
       {
           item &itm = curItems[j];
           painter->save();
           painter->translate(itm.x * WIDTH, itm.y * HEIGHT );
#if DEBUG
           std::cout << "draw x:"<< itm.x  * WIDTH << " y:" << itm.y * HEIGHT << std::endl;
#endif
           qreal radius = 10;
           qreal circleRadius = 20;
           painter->drawEllipse(QRectF(radius, -circleRadius,
                                        circleRadius * 2, circleRadius * 2));
           painter->restore();
       }
    }
#if 0
    painter->rotate(elapsed * 0.030);

    qreal r = elapsed / 1000.0;
    int n = 30;
    for (int i = 0; i < n; ++i) {
        painter->rotate(30);
        qreal factor = (i + r) / n;
        qreal radius = 0 + 120.0 * factor;
        qreal circleRadius = 1 + factor * 20;
        painter->drawEllipse(QRectF(radius, -circleRadius,
                                    circleRadius * 2, circleRadius * 2));
    }
    painter->restore();
#endif
    painter->setPen(textPen);
    painter->setFont(textFont);
    painter->drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, QStringLiteral("Qt"));
    painter->restore();
}
