#include <QApplication>
#include <QDebug>
#include <QDateTime>
#include "../app_version.h"
#include "runner.h"
#include "i8080.h"

#define FREQ 2100000

int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(microsha_res);
    QString version = QString("%1.%2.%3 build [%4]")
            .arg(VER_MAJOR)
            .arg(GIT_VERSION)
            .arg(APP_COMMIT_COUNT)
            .arg(APP_TIME);

    qDebug() <<" version:" <<version;


    QApplication app(argc, argv);
    app.setApplicationName(QString("Microsha QT5 emulator. ver:%1").arg(version));

    i8080 *cpu = new i8080(&app);
    Runner *runner = new Runner(&app);
    runner->setCPU(cpu,FREQ);
    return app.exec();
}
