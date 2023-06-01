#include "rootcontroller.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/qqmlextensionplugin.h>
Q_IMPORT_QML_PLUGIN(aqmltreepluginPlugin)

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    // The first subfolder is the libraryName followed by the regular
    // folder structure: LibraryName/Subfolder
    const QUrl url(u"qrc:/ExampleProjectApp/example/example.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    qmlRegisterSingletonType<RootController>("Palm1r.treeviewProjects.RootController",
                                             1,
                                             0,
                                             "RootController",
                                             [](QQmlEngine *engine, QJSEngine *) {
                                                 auto rootController = new RootController(engine);
                                                 return rootController;
                                             });
    engine.load(url);

    return app.exec();
    //#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    //    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //#endif
    //    QGuiApplication app(argc, argv);

    //    QQmlApplicationEngine engine;
    //    const QUrl url(QStringLiteral("qrc:/example.qml"));
    //    QObject::connect(
    //        &engine,
    //        &QQmlApplicationEngine::objectCreated,
    //        &app,
    //        [url](QObject *obj, const QUrl &objUrl) {
    //            if (!obj && url == objUrl)
    //                QCoreApplication::exit(-1);
    //        },
    //        Qt::QueuedConnection);
    //    qmlRegisterSingletonType<RootController>("Palm1r.treeviewProjects.RootController",
    //                                             1,
    //                                             0,
    //                                             "RootController",
    //                                             [](QQmlEngine *engine, QJSEngine *) {
    //                                                 auto rootController = new RootController(engine);
    //                                                 return rootController;
    //                                             });

    //    engine.load(url);

    //    return app.exec();
}
