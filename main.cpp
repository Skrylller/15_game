#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include "gameboard.h"
#include "timer.h"
#include "gamecontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    GameController gameController;

    engine.rootContext()->setContextProperty("GameModel", gameController.getGameBoard());
    engine.rootContext()->setContextProperty("TimerModel", gameController.getTimer());
    engine.rootContext()->setContextProperty("GameController", gameController.getQObject());

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    gameController.getTimer()->SetActiveTimer(true);

    return app.exec();
}
