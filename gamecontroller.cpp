#include "gamecontroller.h"

GameController::GameController(QObject *parrent) : QObject(parrent)
{
    timer = new Timer(this);
    gameBoard = new GameBoard(4, this);
    dataController = new DataController(this);

    gameBoard->AddOnMove(this);

    moveCount = 0;
    isGameComplete = false;
}

int GameController::GetMoveCount()
{
    return moveCount;
}

void GameController::moveUpdate()
{
    plusMove();
    if(bool isComplete = gameBoard->CheckCompleteBoard()){
        CompleteGame();
    }
}

Timer *GameController::getTimer() const
{
    return timer;
}

QObject *GameController::getQObject()
{
    return this;
}

bool GameController::GetGameComplete()
{
    return isGameComplete;
}

bool GameController::move(int index)
{
    if(isGameComplete)
        return false;

    return gameBoard->move(index);
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

void GameController::CompleteGame()
{
    timer->SetActiveTimer(false);
    isGameComplete = true;
    emit signalGameComplete();
}

void GameController::RestartLevel()
{
    timer->SetActiveTimer(true);
    gameBoard->SelectedCell(-1);
    gameBoard->Shuffle();
    moveCount = 0;
    isGameComplete = false;
    emit signalGameComplete();
    emit signalPlusMove();
}

void GameController::slotRestart()
{
    RestartLevel();
}
