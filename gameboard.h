#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QAbstractListModel>
# include <vector>

class GameBoard : public QAbstractListModel
{
    Q_OBJECT
public:
    static constexpr int defBoardSideSize = 4;
    GameBoard(int sideSize = defBoardSideSize, QObject* parrent = nullptr);

private:
    void Shuffle();

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
