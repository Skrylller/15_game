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
    /// \brief Возвращает значение из Vector клеток по индексу index
    /// \param index
    /// \param role
    /// \return
    ///
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    int sideSize() const;

    int cellNum() const;

    Q_INVOKABLE bool move(int index);

private:

    ///
    /// \brief Перемешивает клетки
    ///
    void Shuffle();

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
