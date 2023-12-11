#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QAbstractListModel>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "gamecontroller.h"
#include "IMoveUpdate.h"

class GameBoard : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int m_sideSize READ sideSize CONSTANT)
    Q_PROPERTY(int m_cellNum READ cellNum CONSTANT)
    Q_PROPERTY(int horizontalAnimDirection READ  getHorizontalAnimDirection WRITE setHorizontalAnimDirection NOTIFY MoveCell)
    Q_PROPERTY(int verticalAnimDirection READ getVerticalAnimDirection WRITE setHorizontalAnimDirection NOTIFY MoveCell)
    Q_PROPERTY(int isAnimRun READ IsAnimRun WRITE IsAnimRun NOTIFY MoveCell)
    Q_PROPERTY(int selectedCell READ SelectedCell WRITE SelectedCell NOTIFY MoveCell)

public:
    static constexpr int defBoardSideSize = 4; //дефолтный размер стороны поля
    using Position = std::pair<int, int>; // по сути typedef std::pair<int, int> pos;

    ///
    /// \brief Конструктор GameBoard, создает поле клеток и перемешивает его.
    /// \param sideSize - размер стороны поля
    /// \param parrent
    ///
    GameBoard(int sideSize = defBoardSideSize, QObject* parrent = nullptr);

    ///
    /// \brief Размер игрового поля (кол-во ячеек)
    /// \param parent
    /// \return
    ///
    int rowCount(const QModelIndex& parent = QModelIndex {}) const override;

    ///
    /// \brief Возвращает значение из Vector клеток по индексу index (qml pyfxtybt display)
    /// \param index
    /// \param role
    /// \return
    ///
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    ///
    /// \brief необходим для настройки окна
    /// \return
    ///
    int sideSize() const;

    ///
    /// \brief необходим для настройки окна
    /// \return
    ///
    int cellNum() const;

    int getHorizontalAnimDirection() const;

    void setHorizontalAnimDirection(int value);

    int getVerticalAnimDirection() const;

    void setVerticalAnimDirection(int value);

    bool IsAnimRun() const;

    void IsAnimRun(bool value);

    int SelectedCell() const;

    void SelectedCell(int value);

    ///
    /// \brief Пробует переместить клетку по заданному индексу на пустое место
    /// \param index
    /// \return
    ///
    bool move(int index);

    void AddOnMove(IMoveUpdate* iMoveUpdate);

    bool CheckCompleteBoard();

    ///
    /// \brief Перемешивает клетки
    ///
    void Shuffle();

private:

    ///
    /// \brief Проверяет входит ли индекс в размер контейнера клеток
    /// \param cellIndex
    /// \return
    ///
    bool isPositionValid(const int cellIndex) const;

    ///
    /// \brief Проверяет является ли поле проходимым (работает некорректно)
    /// \return
    ///
    bool isBoardValid() const;

    ///
    /// \brief Создает pair позиции клетки по индексу
    /// \param index
    /// \return
    ///
    Position getPosition(int index) const;

    void CalcAnimDirection(const GameBoard::Position f, const GameBoard::Position s);

    class Cell{

    public:
        int value;

        Cell& operator=(const int newValue){
            value = newValue;
            return *this;
        }

        bool operator==(int otherVal){
            return value == otherVal;
        }
    };

    std::vector<Cell> m_cells;
    const int m_sideSize;
    const int m_cellNum;

    int animDirectionH = 0;
    int animDirectionV = 0;
    int selectedCell;
    bool isAnimRun;

    std::vector<IMoveUpdate*> moveUpdateObjs;

signals:

    void MoveCell();
};

#endif // GAMEBOARD_H
