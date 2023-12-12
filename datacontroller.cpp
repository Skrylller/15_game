#include "datacontroller.h"

DataController::DataController(QObject *parrent) : QObject(parrent)
{
    leadersFile.setFileName(fileName);
    if(leadersFile.exists())
        qDebug() << leadersFile.fileName() << QStringLiteral(u" существует");
    else
        qDebug() << leadersFile.fileName() << QStringLiteral(u" не существует");

    if(!leadersFile.open(QIODevice::ReadOnly))
        qDebug() << leadersFile.fileName() << QStringLiteral(u" ошибка открытия для чтения");
    leadersFile.close();

    if(!leadersFile.open(QIODevice::WriteOnly))
        qDebug() << leadersFile.fileName() << QStringLiteral(u" ошибка открытия для записи");
    leadersFile.close();

    leaders.push_back({"ff", 0,0});
    Save();
    Load();
}

void DataController::Save()
{
    if(!leadersFile.open(QIODevice::WriteOnly)){
        qDebug() << QStringLiteral(u"Ошибка при открытии файла");
        return;
    }

    QDataStream leaderQdata(&leadersFile);
    leaderQdata << leaders;
    leadersFile.close();
}

void DataController::Load()
{
    if(!leadersFile.open(QIODevice::ReadOnly)){
        qDebug() << QStringLiteral(u"Ошибка при открытии файла");
        return;
    }
    QDataStream leaderQdata(&leadersFile);
    leaders.clear();
    leaderQdata >> leaders;
    leadersFile.close();
}

bool DataController::CheckNewRate(DataController::LeaderData* data)
{
    bool isCheck = false;

    for(auto it = leaders.begin(); it != leaders.end(); ++it){
        if(isCheck && it - leaders.begin() >= numLeaders){
            leaders.erase(it, leaders.end());
        }

        if(it->timeRate > data->timeRate){
            leaders.insert(it, *data);
            isCheck = true;
        }
    }

    if(isCheck)
        Save();

    return isCheck;
}
