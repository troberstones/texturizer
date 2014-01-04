#ifndef TILEDATAMODEL_H
#define TILEDATAMODEL_H

#include <QAbstractTableModel>
#include "tile.h"

class TileDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TileDataModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const
    {
        return m_tile->GetParamCount();
    }

    int columnCount(const QModelIndex &parent) const { return 2; }
    QVariant data(const QModelIndex &index, int role) const
    {
        if(role == Qt::DisplayRole)
        {
            if(index.column()==0)
                return QVariant(m_tile->GetLabelAtIndex(index.row()).c_str());
            else
                return m_tile->GetOrEditValueAtIndex(index.row());
        }
        else if(role == Qt::EditRole)
        {
            if(index.column()==0)
                return QVariant(m_tile->GetLabelAtIndex(index.row()).c_str());
            else
                return m_tile->GetOrEditValueAtIndex(index.row());
        }
        else
            return QVariant();

    }
    QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
        if(orientation == Qt::Horizontal)
        {
            return QVariant("Bar");
            return QVariant(m_tile->GetLabelAtIndex(section).c_str());
        }
        return QVariant();

    }
    Qt::ItemFlags flags(const QModelIndex &index) const
    {
        if(index.column()==1)
            return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
        else
            return Qt::NoItemFlags;
    }
    bool setData(const QModelIndex &index, const QVariant &value, int role)
    {
        if (role == Qt::EditRole)
        {
            int row = index.row();
            int col = index.column();
            if(col == 1)
            {
                m_tile->GetOrEditValueAtIndex(row, 1, value);
                emit dataChanged(index,index);
                return true;
            }
        }
        return false;
    }

signals:

public slots:

public:
   Tile *m_tile;

};

#endif // TILEDATAMODEL_H
