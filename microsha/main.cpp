#include <QApplication>
#include <QDebug>
#include <QDateTime>
#include "../app_version.h"
#include "runner.h"
#include "i8080.h"

#define FREQ 2100000

int main(int argc, char *argv[])
{
    QString version = QString("%1.%2.%3 build time[%4]")
            .arg(VER_MAJOR)
            .arg(GIT_VERSION)
            .arg(APP_COMMIT_COUNT)
            .arg(APP_TIME);

    qDebug() << "APP_TIME:"<<APP_TIME<< " version:" <<version;

    //Q_INIT_RESOURCE(microsha_res);
    QApplication app(argc, argv);
    app.setApplicationName(QString("Microsha QT5 emulator. ver:%1").arg(version));

    i8080 *cpu = new i8080(&app);
    Runner *runner = new Runner(&app);
    runner->setCPU(cpu,FREQ);
    return app.exec();
}
