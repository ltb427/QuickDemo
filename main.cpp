#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "colormaker.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    // 注册一个 QML 类型 ;注册一个单例类型,然后就可以在qml里面调用了
    //qmlRegisterType() 的第一个参数 uri ，让你指定一个唯一的包名，类似 Java 中的那种，
    //一是用来避免名字冲突，而是可以把多个相关类聚合到一个包中方便引用。
    //比如我们常写这个语句 "import QtQuick.Controls 1.1" ，其中的 "QtQuick.Controls" 就是包名 uri ，而 1.1 则是版本，是 versionMajor 和 versionMinor 的组合。
    //qmlName 则是 QML 中可以使用的类名。


    qmlRegisterType<ColorMaker>("qt.an.colormaker", 1, 0, "ColorMaker");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
