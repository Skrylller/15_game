#include "timer.h"

Timer::Timer(time_t startTime, QObject* parrent) : QObject(parrent)
{
    this->startTime = startTime;
}

Timer::Timer(QObject* parrent) : QObject(parrent)
{
    Timer(CurrentTime(), parrent);
}

void Timer::SetActiveTimer(bool isActive)
{
    this->isActive = isActive;
    currentTime = CurrentTime();

    if(isActive){
        startTime = CurrentTime();
        if(updateTimer == nullptr){
            updateTimer = new QTimer(this);
            connect(updateTimer, SIGNAL(timeout()), this, SLOT(slotUpdate()));
        }
        updateTimer->start(500);
    }

    if(!isActive){
        updateTimer->stop();
    }

    emit TimerUpdate();
}

bool Timer::IsActive()
{
    return isActive;
}

time_t Timer::GetDifTime()
{
    return  CurrentTime() - startTime;
}

void Timer::slotUpdate()
{
    if(currentTime == CurrentTime())
        return;

    currentTime = CurrentTime();
    emit TimerUpdate();
}

QString Timer::GetTimeSeconds()
{
    int sec = GetDifTime() % 60;
    return sec < 10 ? "0" + QString::number(sec) : QString::number(sec);
}

QString Timer::GetTimeMinutes()
{
    int min = GetDifTime() / 60;
    return min < 10 ? "0" + QString::number(min) : QString::number(min);
}

time_t Timer::CurrentTime()
{
    //auto time = std::chrono::system_clock::now();
    //return std::chrono::system_clock::to_time_t(time);
    return time(NULL);
}
