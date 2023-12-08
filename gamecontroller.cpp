#include "gamecontroller.h"

GameController::GameController(QObject *parrent) : QObject(parrent)
{
    timer = new Timer(this);
    gameBoard = new GameBoard(4, this);

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

    emit signalPlusMove();
}

void GameController::SetGameBoard(GameBoard* gameBoard)
{
    this->gameBoard = gameBoard;

    gameBoard->AddOnMove(this);
}
