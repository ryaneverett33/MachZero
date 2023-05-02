#include "machzero/views/MainWindow.h"
#include "machzero/views/SplashScreen.h"
#include "machzero/WindowManager.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "MachOViewer_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    WindowManager::getInstance().showSplashScreen();
    return a.exec();
}
