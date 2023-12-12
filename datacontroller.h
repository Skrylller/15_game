#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H
#include <QFile>
#include <QDebug>
#include <QDataStream>

class DataController : QObject
{

public:
    class LeaderData{
    public:
        QString name;
        time_t timeRate;
        int moveCount;

        friend QDataStream &operator <<(QDataStream &out, const DataController::LeaderData &data)
        {
            out << data.name;
            out << data.timeRate;
            out << data.moveCount;
            return out;
        }

        friend QDataStream &operator >>(QDataStream &out, DataController::LeaderData &data)
        {
            out >> data.name;
            out.skipRawData(sizeof(data.name));
            out >> data.timeRate;
            out.skipRawData(sizeof(data.timeRate));
            out >> data.moveCount;
            out.skipRawData(sizeof(data.moveCount));
            return out;
        }
    };

    DataController(QObject *parrent = nullptr);

    void Save();

    void Load();

    bool CheckNewRate(LeaderData* data);

private:

    QString const fileName = "leaders.data";
    int const numLeaders = 3;

    QFile leadersFile;
    QVector<LeaderData> leaders;
};

#endif // DATACONTROLLER_H
