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
public:
    GameController(QObject* parrent = nullptr);

    int GetMoveCount();

    void moveUpdate() override;

    GameBoard *getGameBoard() const;

    Timer *getTimer() const;

    QObject *getQObject();

private:
    GameBoard* gameBoard = nullptr;
    Timer* timer;

    int fieldSideSize = 4;
    int moveCount = 0;

    void plusMove();

signals:

    void signalPlusMove();

private slots:

    void SetGameBoard(GameBoard* gameBoard);

};

#endif // GAMECONTROLLER_H
