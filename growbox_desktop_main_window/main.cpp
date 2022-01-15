#include "mainwindow.h"
//#include "anotherwindow.h"

#include "connection.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Connect to MS Azure Database
    //if (!createConnection())
    //    return 1;

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "growbox_desktop_main_window_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w("sensor_values");;
    w.show();
    return a.exec();
}
