#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QAbstractListModel>
#include "IMoveUpdate.h"
#include "gameboard.h"
#include "timer.h"

class GameBoard;

class GameController : public QObject, public IMoveUpdate
{
    Q_OBJECT
    Q_PROPERTY(int moveCount READ  GetMoveCount NOTIFY signalPlusMove)
    Q_PROPERTY(bool gameComplete READ GetGameComplete NOTIFY signalGameComplete)
public:
    GameController(QObject* parrent = nullptr);

    int GetMoveCount();

    void moveUpdate() override;

    GameBoard *getGameBoard() const;

    Timer *getTimer() const;

    QObject *getQObject();

    bool GetGameComplete();

    ///
    /// \brief Пробует переместить клетку по заданному индексу на пустое место
    /// \param index
    /// \return
    ///
    Q_INVOKABLE bool move(int index);

private:
    GameBoard* gameBoard = nullptr;
    Timer* timer;

    bool isGameComplete;

    int fieldSideSize = 4;
    int moveCount = 0;

    void plusMove();

    void CompleteGame();

    void RestartLevel();

signals:

    void signalGameComplete();
    void signalPlusMove();

public slots:

    void slotRestart();

};

#endif // GAMECONTROLLER_H
