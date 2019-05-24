#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>

#include <stdio.h>
#include <QDebug>
#include <QQmlContext>
#include <QFileSystemModel>
#include <QItemSelectionModel>
#include <QRegExp>

#include "StreamInfo.h"
#include "FileModel.h"


int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterUncreatableType<FileInfo>       ("ffmpegFilesInfo", 1, 0, "FileInfo"     , "Type cannot be created in QML");
    qmlRegisterUncreatableType<StreamInfo>     ("ffmpegFilesInfo", 1, 0, "StreamInfo"   , "Type cannot be created in QML");
    qmlRegisterUncreatableType<StreamDetail>   ("ffmpegFilesInfo", 1, 0, "StreamDetail" , "Type cannot be created in QML");

    QQmlContext *ctxt = engine.rootContext();

    FileModel fileModel;

    ctxt->setContextProperty("fileModel", &fileModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
