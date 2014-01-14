#include <iostream>
#include <vector>

#include "tilemanager.h"

TileManager::TileManager()
{
    std::cout << "TileManager Ctor called" << std::endl;
}

TileManager::~TileManager()
{
    std::cout << "TileManager dtor" << std::endl;
}

void TileManager::AddTile()
{
    int size = (int)m_tileVector.size();
    char nameBuf[21];
    sprintf_s(nameBuf, "Tile_%d", size);
    Tile newTile;
    newTile.SetName(std::string(nameBuf));
    m_tileVector.push_back(newTile);
}

void TileManager::RemoveTile(int tileIndex)
{
    std::cout << "Need to remove tile:" << tileIndex
              << " from the tileVector" << std::endl;
    std::vector<Tile>::iterator it= m_tileVector.begin();
    it += tileIndex; // increment iterator to the desired index
    m_tileVector.erase(it);
}

int TileManager::GetCount()
{
    return static_cast<int>(m_tileVector.size());
}

std::string TileManager::GetName(int tileIndex)
{
    return m_tileVector[tileIndex].GetName();
}

std::string TileManager::GetMemo(int tileIndex)
{
    return m_tileVector[tileIndex].GetMemo();
}

void TileManager::SetName(int tileIndex, std::string &name)
{
    m_tileVector[tileIndex].SetName(name);
}

void TileManager::SetMemo(int tileIndex, std::string &memo)
{

    m_tileVector[tileIndex].SetMemo(memo);
}
Tile & TileManager::GetTile(int tileIndex)
{
    return m_tileVector[tileIndex];
}

const std::vector<Tile> &TileManager::GetTiles() const
{
    return m_tileVector;
}

void TileManager::Prep()
{
   // Loop over tiles and populate them
    for(int i = 0; i < GetCount(); ++i)
    {
        m_tileVector[i].Populate();

    }
}
