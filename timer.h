#ifndef TIMER_H
#define TIMER_H
#include <QAbstractListModel>
#include <QTime>
#include <QTimer>
#include "windows.h"

class Timer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString minutes READ  GetTimeMinutes NOTIFY TimerUpdate)
    Q_PROPERTY(QString seconds READ GetTimeSeconds NOTIFY TimerUpdate)


public:
    Timer(QObject* parrent = nullptr);

    Timer(time_t startTime, QObject* parrent = nullptr);

    void SetActiveTimer(bool isActive);

    bool IsActive();

    QString GetTimeSeconds();

    QString GetTimeMinutes();

    QTimer *updateTimer = nullptr;

private:
    time_t CurrentTime();

    time_t GetDifTime();

    time_t startTime = time(0);
    time_t currentTime = time(0);
    bool isActive = false;

signals:

    void TimerUpdate();

private slots:

    void slotUpdate();
};

#endif // TIMER_H
