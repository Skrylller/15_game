#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <QAbstractListModel>
#include "gameboard.h"
#include "timer.h"
#include "IMoveUpdate.h"


class GameController : public QObject, public IMoveUpdate
{
    Q_OBJECT
    Q_PROPERTY(int moveCount READ  GetMoveCount NOTIFY moveUpdate)
public:
    GameController(GameBoard *gameboard, QObject* parrent = nullptr);

    int GetMoveCount();

    void moveUpdate() override;

private:
    GameBoard *gameBoard = nullptr;
    Timer *timer = nullptr;

    int moveCount = 0;

    void plusMove();

signals:

    void signalPlusMove();

};

#endif // GAMECONTROLLER_H
