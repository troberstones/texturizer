#include "renderer.h"
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QWidget>

#include "tilemanager.h"
#include "tile.h"
#include <iostream>

#define RADTODEG 57.29f

Renderer::Renderer():
    m_tileManager(0)
{
    if(m_tileManager)
        m_tileManager->Prep();
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::white);
    gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));
    m_background = QBrush(QColor(64, 32, 64));
    m_color.setRgbF(1.f, 0, 0, 1.f);
    m_tileBrush = QBrush(m_color);

    m_tilePen = QPen(Qt::black);
    m_tilePen.setWidth(1);
    m_textPen = QPen(Qt::white);
    m_textFont.setPixelSize(50);
}

void Renderer::SetTileManager(TileManager *inputManager)
{
   m_tileManager = inputManager;
   m_tileManager->Prep();
}

void Renderer::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    QString fileName = "C:\\Users\\Charvey\\Pictures\\cloverTestTile.png";
    QImage testTile;
    if(!testTile.load(fileName))
        std::cout << "Image Failed to load" << std::endl;
    std::cout << "Image loaded. H:" << testTile.height() << " W:" << testTile.width() << std::endl;
    //m_tileBrush = QBrush(testTile);
    m_tileBrush.setTextureImage(testTile);
    m_tileBrush.setStyle(Qt::TexturePattern);
    m_tileBrush.setTransform(QTransform().scale(.1f,.1f));
    painter->fillRect(event->rect(), m_background);
    if(!m_tileManager)
    {
        std::cout << "Renderer: No Tile Manager!" << std::endl;
        return;
    }

    painter->save();
    painter->setBrush(m_tileBrush);
    painter->setPen(m_tilePen);

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
       float invSplatCount = 1.f/splatCount;
       painter->setPen(Qt::NoPen);
       for(size_t j = 0; j < splatCount; ++j)
       {
           item &itm = curItems[j];
           painter->save();
           painter->translate(itm.x * m_xres, itm.y * m_yres);
#if DEBUG
           std::cout << "draw x:"<< itm.x  * m_xres << " y:" << itm.y * m_yres << std::endl;
#endif
#ifdef TESTCOLORBRUSH
           float tmp = j * invSplatCount;
           m_color.setRedF(tmp);
           m_tileBrush.setColor(m_color);
           painter->setBrush(m_tileBrush);
           float r, g, b;
           tile.GetColor(r,g,b);
           //m_tileBrush.setColor(QColor(255,0,0,128));
#endif
           painter->rotate(itm.rotate * RADTODEG);
           painter->drawRect(itm.x, itm.y, itm.w, itm.h);
           //std::cout << " Width/height: " << itm.w << std::endl;
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
    painter->setPen(m_textPen);
    painter->setFont(m_textFont);
    painter->drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, QStringLiteral("Qt"));
    painter->restore();
}
