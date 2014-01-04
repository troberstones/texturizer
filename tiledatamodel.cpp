#include "tiledatamodel.h"
#include <iostream>

TileDataModel::TileDataModel(QObject *parent) :
    QAbstractTableModel(parent),
    m_tile(0)
{
    std::cout << "tile model ctor" << std::endl;
}
