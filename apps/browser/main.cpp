#include <QApplication>
#include <components/settings/settings.hpp>
#include <components/files/configurationmanager.hpp>
#include <apps/browser/netutils/QueryClient.hpp>
#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow d;

    d.show();
    return app.exec();
}
