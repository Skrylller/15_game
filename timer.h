#ifndef TIMER_H
#define TIMER_H
#include <QAbstractListModel>
#include <QTime>
#include <QTimer>

class Timer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int minutes READ  GetTimeMinutes NOTIFY TimerUpdate)
    Q_PROPERTY(int seconds READ GetTimeSeconds NOTIFY TimerUpdate)

public:
    Timer(QObject* parrent = nullptr);

    Timer(time_t startTime, QObject* parrent = nullptr);

    bool IsActive();

    int GetTimeSeconds();

    int GetTimeMinutes();

    QTimer *updateTimer;

private:
    void SetActiveTimer(bool isActive);

    time_t CurrentTime();

    tm& GetTm();

    time_t startTime = time(0);
    time_t currentTime = time(0);
    bool isActive = false;

signals:

    void TimerUpdate();

private slots:

    void Update();
};

#endif // TIMER_H
