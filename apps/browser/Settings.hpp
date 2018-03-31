//
// Created by koncord on 31.03.18.
//

#pragma once

#include <components/settings/settings.hpp>

namespace Ui
{
    class MainWindow;
}

class SettingsMgr
{
public:
    SettingsMgr();

    void loadBrowserSettings(Ui::MainWindow &mw);
    void saveBrowserSettings(Ui::MainWindow &mw);

    void loadClientSettings(Ui::MainWindow &mw);
    void saveClientSettings(Ui::MainWindow &mw);

    void loadServerSettings(Ui::MainWindow &mw);
    void saveServerSettings(Ui::MainWindow &mw);

private:
    Settings::Manager serverMgr, clientMgr;
    std::string serverCfg, clientCfg;
    void switchMgr();
};
