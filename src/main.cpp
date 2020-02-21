#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>

#include "environmentinitializer.h"

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("Amarger Corp.");
    QCoreApplication::setApplicationName("Smart Weather Station");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    EnvironmentInitializer::getInstance().initialize(engine.rootContext());

    engine.load(url);

    return app.exec();
}
