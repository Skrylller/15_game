#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QAbstractListModel>
# include <vector>

class GameBoard : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int m_sideSize READ sideSize CONSTANT)
    Q_PROPERTY(int m_cellNum READ cellNum CONSTANT)

public:
    static constexpr int defBoardSideSize = 4;
    using Position = std::pair<int, int>;

    GameBoard(int sideSize = defBoardSideSize, QObject* parrent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex {}) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    int sideSize() const;

    int cellNum() const;

    Q_INVOKABLE bool move(int index);

private:
    void Shuffle();
    bool isPositionValid(const int cellIndex) const;
    bool isBoardValid() const;
    Position getRowCol(int index) const;

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
};

#endif // GAMEBOARD_H
