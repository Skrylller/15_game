#include "gameboard.h"
#include <algorithm>
#include <random>

GameBoard::GameBoard(int sideSize, QObject* parrent) : QAbstractListModel(parrent),
    m_sideSize (sideSize),
    m_cellNum (sideSize * sideSize)
{
    m_cells.resize(m_cellNum);
    std::iota(m_cells.begin(), m_cells.end(), 1);
    Shuffle();
}

void GameBoard::Shuffle()
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 generator(seed);

    std::shuffle(m_cells.begin(), m_cells.end(), generator);
}
