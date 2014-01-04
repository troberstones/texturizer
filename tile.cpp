#include <iostream>

#include "tile.h"
#include <cstdlib> // rand
// A tile is a data object that embodies the capabilites
// of a tiler tile. Each tile can be rendered to the target
// canvas and has a number of controls which affect the
// appearance


Tile::Tile():
    s_labels(0),
    m_tileCount(0),
    m_mode(kUniform),
    m_texture(""),
    m_name("default"),
    m_memo("memoVal"),
    m_rotate(),
    m_rotateRange(0),
    m_scale(0),
    m_scaleRange(0),
    m_width(0),
    m_widthRange(0),
    m_height(0),
    m_heightRange(0),
    m_xscale(0),
    m_yscale(0),
    m_jitter(0)
{
    if(s_labels.size() == 0)
        initLabels();
    std::cout << "Base ctor"  << std::endl;
}

Tile::Tile(std::string name):
    m_name(name),
    s_labels(0),
    m_tileCount(0),
    m_mode(kUniform),
    m_texture(""),
    m_memo("memoVal"),
    m_rotate(),
    m_rotateRange(0),
    m_scale(0),
    m_scaleRange(0),
    m_width(0),
    m_widthRange(0),
    m_height(0),
    m_heightRange(0),
    m_xscale(0),
    m_yscale(0),
    m_jitter(0)
{
    if(s_labels.size() == 0)
        initLabels();
    std::cout << "name ctor" << std::endl;
    m_seed = rand();
}

void Tile::Populate()
{
    //XXX
    //std::vector<items> foo;
    if(m_tiles.size() == m_tileCount)
    {
        std::cout << "Tile:Populate: size:" << m_tiles.size() << "tileCount request:" << m_tileCount << std::endl;
        return;
    }
    else
    {
        m_tiles.clear();
    }
    srand(m_seed);
    // Need to check for changes
    m_tiles.reserve(m_tileCount);
    for(int i = 0; i < m_tileCount; ++i)
    {
        float x = (rand()%100) / 100.f;
        float y = (rand()%100) / 100.f;
        item tmp(x, y, 0.f, 1.f, 1.f, 0.f);
        std::cout << "push:" << i << std::endl;
        m_tiles.push_back(tmp);
    }
}

item::item(float inx, float iny, float inz, float width, float height, float rot):
    x(inx), y(iny), z(inz), w(width), h(height), rotate(rot)
{
    std::cout << "ctor called" << std::endl;
}

item::~item()
{
    std::cout << "dtor called" << std::endl;
}

void item::setTile(const float &inx, const float &iny, const float &inz, const float &inw,
                   const float &inh, const float &inrot)
{
    x = inx;
    y = iny;
    z = inz;
    w = inw;
    h = inh;
    rotate = inrot;
}

// Hit test the item and fill in the s and t of the hit. Return true if hit
bool item::intersect(const float &testX, const float &testY, float &hitS, float &hitT)
{
    // xform test point into tile space.
    // then test against simpleer bounds
    float tX = testX - x;
    float tY = testY - y;
    if(tX > 0 && tX < w &&
       tY > 0 && tY < h)
    {
        // if we hit the tile, normalize
        // the position to the tile pos and
        // return
        hitS = tX/w;
        hitT = tY/h;
        return true;
    }
    return false;
}
