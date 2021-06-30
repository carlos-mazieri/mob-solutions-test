#include "gadgets/p2d.h"
#include "gadgets/player.h"
#include "gadgets/gadgethelper.h"

#include <custommodel.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);  
    qRegisterMetaType<Player>("Player");
    qRegisterMetaType<P2D>("P2D");
    qmlRegisterType<CustomModel>("com.test.models", 1, 0, "CustomModel");


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    GadgetHelper gadgetHelper(const_cast<QMetaObject*> (&Player::staticMetaObject));
    engine.rootContext()->setContextProperty("gadgetHelper", &gadgetHelper);
    engine.load(url);

    return app.exec();
}
