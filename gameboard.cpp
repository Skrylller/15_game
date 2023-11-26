#include "gameboard.h"
#include <algorithm>
#include <random>

namespace
{
bool isAdjacent(const GameBoard::Position f, const GameBoard::Position s){
    if(f == s){
        return false;
    }
    const auto calcDistance = [](const int pos1, int pos2){
        int distance = pos1;
        distance -= pos2;
        distance = std::abs(distance);
        return distance;
    };

    bool result = false;

    if (f.first == s.first) {
        int distance = calcDistance(f.second, s.second);
        if(distance == 1){
            result = true;
        }
    }
    else if (f.second == s.second){
        int distance = calcDistance(f.first, s.first);
        if (distance == 1){
            result = true;
        }
    }
    return result;
}
}

GameBoard::GameBoard(int sideSize, QObject* parrent) : QAbstractListModel(parrent),
    m_sideSize (sideSize),
    m_cellNum (sideSize * sideSize)
{
    m_cells.resize(m_cellNum);
    std::iota(m_cells.begin(), m_cells.end(), 1);
    Shuffle();
}

int GameBoard::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_cells.size();
}

QVariant GameBoard::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
    {
        return {};
    }

    const int cellIndex {index.row()};

    if (!isPositionValid(cellIndex))
    {
        return {};
    }

    return QVariant::fromValue(m_cells.at(cellIndex).value);
}

void GameBoard::Shuffle()
{
    static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 generator(seed);

    do
    {
        std::shuffle(m_cells.begin(), m_cells.end(), generator);
    } while (isBoardValid());
}

bool GameBoard::isPositionValid(const int cellIndex) const
{
    return cellIndex < m_cellNum;
}

bool GameBoard::isBoardValid() const
{
    int inv = 0;
    for (int i = 0; i < m_cellNum; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if(m_cells[j].value > m_cells[i].value)
            {
                ++inv;
            }
        }
    }

    const int start_point = 1;

    for (int i = 0; i < m_cellNum; ++i)
    {
        if(m_cells[i].value == m_cellNum)
        {
            inv += start_point + i / m_sideSize;
        }
    }

    return (inv % 2) == 0;
}

GameBoard::Position GameBoard::getRowCol(int index) const
{
    Q_ASSERT(m_sideSize > 0);
    int row = index / m_sideSize;
    int column = index % m_sideSize;

    return std::make_pair(row, column);
}

int GameBoard::cellNum() const
{
    return m_cellNum;
}

bool GameBoard::move(const int index)
{
    if(!isPositionValid(index))
    {
        return false;
    }

    const Position elementPosition = getRowCol(index);

    auto hiddenElementIterator = std::find(m_cells.begin(), m_cells.end(), cellNum());

    Q_ASSERT(hiddenElementIterator != m_cells.end());

    Position hiddenElementPosition = getRowCol(std::distance(m_cells.begin(), hiddenElementIterator));

    if(!isAdjacent(elementPosition, hiddenElementPosition)){
        return false;
    }
    std::swap(hiddenElementIterator->value, m_cells[index].value);
    emit dataChanged(createIndex(0, 0), createIndex(m_cellNum, 0));

    return true;
}

int GameBoard::sideSize() const
{
    return m_sideSize;
}
