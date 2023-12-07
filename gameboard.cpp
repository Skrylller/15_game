#include "gameboard.h"
#include <algorithm>
#include <random>
#include <cmath>

namespace
{
///
/// \brief Проверка находится ли позиция рядом с пустой ячейкой.
/// \param f - первая позиция
/// \param s - вторая позиция
/// \return
///
bool isAdjacent(const GameBoard::Position f, const GameBoard::Position s){
    if(f == s){
        return false;
    }

    // Считает дистанцию между двумя значениями.
    const auto calcDistance = [](const int pos1, int pos2){
        int distance = pos1;
        distance -= pos2;
        distance = std::abs(distance);
        return distance;
    };

    //Проверка дистанции по горизонтали.
    if (f.first == s.first) {
        int distance = calcDistance(f.second, s.second);
        if(distance == 1){
            return true;
        }
    }
    //Проверка дистанции по вертикали.
    else if (f.second == s.second){
        int distance = calcDistance(f.first, s.first);
        if (distance == 1){
            return true;
        }
    }

    return false;
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

GameBoard::Position GameBoard::getPosition(int index) const
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

int GameBoard::getHorizontalAnimDirection() const
{
    return animDirectionH;
}

void GameBoard::setHorizontalAnimDirection(int value)
{
    animDirectionH = value;
}

int GameBoard::getVerticalAnimDirection() const
{
    return animDirectionV;
}

void GameBoard::setVerticalAnimDirection(int value)
{
    animDirectionV = value;
}

bool GameBoard::IsAnimRun() const
{
    return isAnimRun;
}

void GameBoard::IsAnimRun(bool value)
{
    isAnimRun = value;
}

int GameBoard::SelectedCell() const
{
    return selectedCell;
}

void GameBoard::SelectedCell(int value)
{
    selectedCell = value;
}

bool GameBoard::move(const int index)
{
    if(!isPositionValid(index))
    {
        return false;
    }

    //элемент на который нажали
    const Position elementPosition = getPosition(index);

    //итератор последнего элемента
    auto hiddenElementIterator = std::find(m_cells.begin(), m_cells.end(), cellNum());

    //если последний элемент не найден - ошибка с закрытием
    Q_ASSERT(hiddenElementIterator != m_cells.end());

    //позиция посл. элемента
    Position hiddenElementPosition = getPosition(std::distance(m_cells.begin(), hiddenElementIterator));

    //проверка, что выбранный элемент рядом с последним
    if(!isAdjacent(elementPosition, hiddenElementPosition)){
        return false;
    }
    CalcAnimDirection(elementPosition, hiddenElementPosition);

    //меняетр местами значения элементов
    std::swap(hiddenElementIterator->value, m_cells[index].value);

    IsAnimRun(true);
    SelectedCell(hiddenElementIterator->value);

    for(size_t i = 0; i < moveUpdateObjs.size(); i++)
    {
        moveUpdateObjs[i].moveUpdate();
    }

    emit MoveCell();
    emit dataChanged(createIndex(0, 0), createIndex(m_cellNum, 0));
    return true;
}

int GameBoard::sideSize() const
{
    return m_sideSize;
}

void GameBoard::CalcAnimDirection(const GameBoard::Position f, const GameBoard::Position s){
    setHorizontalAnimDirection(0);
    setVerticalAnimDirection(0);

    if (f.first != s.first)
        setVerticalAnimDirection((f.first - s.first) / abs(f.first - s.first));

    if (f.second != s.second)
        setHorizontalAnimDirection((f.second - s.second) / abs(f.second - s.second));
}
