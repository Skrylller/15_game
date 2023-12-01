#include "timer.h"

Timer::Timer(time_t startTime, QObject* parrent) : QObject(parrent)
{
    this->startTime = startTime;
    SetActiveTimer(true);
    updateTimer = new QTimer(this);
    updateTimer->setInterval(1000);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(Update()));
    updateTimer->start();
}

Timer::Timer(QObject* parrent) : QObject(parrent)
{
    Timer(CurrentTime(), parrent);
}

void Timer::SetActiveTimer(bool isActive)
{
    this->isActive = isActive;
}

bool Timer::IsActive()
{
    return isActive;
}

tm& Timer::GetTm()
{
    time_t time = CurrentTime() - startTime;
    struct tm *tm_time = localtime(&time);
    return *tm_time;
}

void Timer::Update()
{
    if(currentTime == CurrentTime())
        return;

    currentTime = CurrentTime();
    emit TimerUpdate();
}

int Timer::GetTimeSeconds()
{
    return GetTm().tm_sec;
}

int Timer::GetTimeMinutes()
{
    return GetTm().tm_min + GetTm().tm_hour * 100;
}

time_t Timer::CurrentTime()
{
    //auto time = std::chrono::system_clock::now();
    //return std::chrono::system_clock::to_time_t(time);
    return time(NULL);
}
