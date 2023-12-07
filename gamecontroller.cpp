#include "gamecontroller.h"

GameController::GameController(GameBoard* gameBoard, Timer* timer, QObject *parrent) : QObject(parrent)
{
    this->gameBoard = gameBoard;
    this->timer = timer;

    gameBoard->moveUpdateObjs.insert(gameBoard->moveUpdateObjs.begin(), this);
}

int GameController::GetMoveCount()
{
    return moveCount;
}

void GameController::moveUpdate()
{
    plusMove();
}

void GameController::plusMove()
{
    ++moveCount;

    emit moveUpdate();
}
