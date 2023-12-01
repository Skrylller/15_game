#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "gameboard.h"
#include "timer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    GameBoard board;
    Timer timer {};

    qmlRegisterType<GameBoard>("Game", 1, 0, "GameBoardModel");
    engine.rootContext()->setContextProperty("TimerModel", &timer);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
