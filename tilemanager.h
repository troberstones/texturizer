#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include "tile.h"
#include <vector>

class TileManager
{
public:
    TileManager();
    ~TileManager();
    void AddTile();
    void RemoveTile(int tileIndex);
    int GetCount();
    std::string GetName(int tileIndex);
    std::string GetMemo(int tileIndex);
    void SetName(int tileIndex, std::string &name);
    void SetMemo(int tileIndex, std::string &memo);
    const std::vector<Tile> &GetTiles() const;
    void Prep();

    Tile &GetTile(int tileIndex);
private:
    std::vector<Tile> m_tileVector;
};

#endif // TILEMANAGER_H
