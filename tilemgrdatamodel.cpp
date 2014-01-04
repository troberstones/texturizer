#include "tilemgrdatamodel.h"
#include "tilemanager.h"

#include <iostream>

TileMgrDataModel::TileMgrDataModel(TileManager *mgr, QObject *parent) :
    QAbstractListModel(parent),
    m_tileManager(mgr)
{

    std::cout << "ctor 6" << std::endl;
}

QModelIndex TileMgrDataModel::index(int row, int column, const QModelIndex &parent) const
{
    //std::cout << "5" << std::endl;
    return createIndex(row,column);
}

QModelIndex TileMgrDataModel::parent(const QModelIndex &child) const
{
    //std::cout << "4" << std::endl;
    return QModelIndex();
}

int TileMgrDataModel::rowCount(const QModelIndex &parent) const
{
    //std::cout << "3" << std::endl;
    return m_tileManager->GetCount();
}

int TileMgrDataModel::columnCount(const QModelIndex &parent) const
{
    //std::cout << "2" << std::endl;
    return 1;
}

QVariant TileMgrDataModel::data(const QModelIndex &index, int role) const
{
    //std::cout << "1" << std::endl;
    int row = index.row();
    int col = index.column();
    if(role == Qt::DisplayRole)
    {
        QString result(m_tileManager->GetName(row).c_str());
        return QVariant(result);
    }
    else
        return QVariant();
}

Tile & TileMgrDataModel::GetTile(const QModelIndex &index)
{
    int row = index.row();
    return m_tileManager->GetTile(row);
}
