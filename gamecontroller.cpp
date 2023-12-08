#include "gamecontroller.h"

GameController::GameController(QObject *parrent) : QObject(parrent)
{
    gameBoard = new GameBoard(fieldSideSize, this);
    timer = new Timer(this);

    gameBoard->AddOnMove(this);
}

int GameController::GetMoveCount()
{
    return moveCount;
}

void GameController::moveUpdate()
{
    plusMove();
}

Timer *GameController::getTimer() const
{
    return timer;
}

QObject *GameController::getQObject()
{
    return this;
}

GameBoard *GameController::getGameBoard() const
{
    return gameBoard;
}

void GameController::plusMove()
{
    ++moveCount;

    emit moveUpdate();
}
