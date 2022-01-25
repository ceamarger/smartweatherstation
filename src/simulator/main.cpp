#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>

#include "scriptlauncher.h"

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("Amarger Corp.");
    QCoreApplication::setApplicationName("Smart Weather Station Simulator");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main_simulator.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    ScriptLauncher scriptLauncher;
    engine.rootContext()->setContextProperty("scriptLauncher", &scriptLauncher);

    qmlRegisterUncreatableType<ScriptLauncher>(
        "sensorSimulator", 1, 0, "ScriptLauncher", "Not creatable");

    engine.load(url);

    return app.exec();
}
