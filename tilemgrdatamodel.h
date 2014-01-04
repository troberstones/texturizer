#ifndef TILEMGRDATAMODEL_H
#define TILEMGRDATAMODEL_H

#include <QAbstractListModel>

class Tile;
class TileManager;

class TileMgrDataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TileMgrDataModel(TileManager *mgr, QObject *parent = 0);
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    Tile &GetTile(const QModelIndex &index);
signals:

public slots:

private:
   TileManager *m_tileManager;

};

#endif // TILEMGRDATAMODEL_H
