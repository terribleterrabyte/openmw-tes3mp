//
// Created by koncord on 31.03.18.
//

#include "Settings.hpp"
#include <QDebug>

#include <components/files/configurationmanager.hpp>
#include <apps/browser/netutils/QueryClient.hpp>
#include "MainWindow.hpp"

std::string loadSettings (Settings::Manager & settings, const std::string &cfgName)
{
    Files::ConfigurationManager mCfgMgr;
    // Create the settings manager and load default settings file
    const std::string localdefault = (mCfgMgr.getLocalPath() / (cfgName + "-default.cfg")).string();
    const std::string globaldefault = (mCfgMgr.getGlobalPath() / (cfgName + "-default.cfg")).string();

    // prefer local
    if (boost::filesystem::exists(localdefault))
        settings.loadDefault(localdefault);
    else if (boost::filesystem::exists(globaldefault))
        settings.loadDefault(globaldefault);
    else
        throw std::runtime_error ("No default settings file found! Make sure the file \"" + cfgName + "-default.cfg\" was properly installed.");

    // load user settings if they exist
    const std::string settingspath = (mCfgMgr.getUserConfigPath() / (cfgName + ".cfg")).string();
    if (boost::filesystem::exists(settingspath))
        settings.loadUser(settingspath);

    return settingspath;
}

SettingsMgr::SettingsMgr()
{
    clientCfg = loadSettings(clientMgr, "tes3mp-client");
    switchMgr();
    serverCfg = loadSettings(serverMgr, "tes3mp-server");
    switchMgr();

    std::string addr = clientMgr.getString("address", "Master");
    int port = clientMgr.getInt("port", "Master");
    QueryClient::Get().SetServer(addr, port);

}

void SettingsMgr::loadBrowserSettings(Ui::MainWindow &mw)
{
    mw.comboLatency->setCurrentIndex(clientMgr.getInt("maxLatency", "Browser"));
    mw.leGamemode->setText(QString::fromStdString(clientMgr.getString("gameMode", "Browser")));
    mw.cBoxNotFull->setCheckState(clientMgr.getBool("notFull", "Browser") ? Qt::Checked : Qt::Unchecked);
    mw.cBoxWithPlayers->setCheckState(clientMgr.getBool("withPlayers", "Browser") ? Qt::Checked : Qt::Unchecked);
    mw.cBBoxWOPass->setCheckState(clientMgr.getBool("noPassword", "Browser") ? Qt::Checked : Qt::Unchecked);

    mw.tblServerBrowser->sortByColumn(clientMgr.getInt("sortByCol", "Browser"),
                                      clientMgr.getBool("sortByColAscending", "Browser") ? Qt::AscendingOrder : Qt::DescendingOrder);

    loadClientSettings(mw);
    switchMgr();
    loadServerSettings(mw);
    switchMgr();
}

void SettingsMgr::saveBrowserSettings(Ui::MainWindow &mw)
{
    clientMgr.setInt("maxLatency", "Browser", mw.comboLatency->currentIndex());
    clientMgr.setString("gameMode", "Browser", mw.leGamemode->text().toStdString());
    clientMgr.setBool("notFull", "Browser", mw.cBoxNotFull->checkState() == Qt::Checked);
    clientMgr.setBool("withPlayers", "Browser", mw.cBoxWithPlayers->checkState() == Qt::Checked);
    clientMgr.setBool("noPassword", "Browser", mw.cBBoxWOPass->checkState() == Qt::Checked);

    clientMgr.setInt("sortByCol", "Browser", mw.tblServerBrowser->horizontalHeader()->sortIndicatorSection());
    clientMgr.setBool("sortByColAscending", "Browser", mw.tblServerBrowser->horizontalHeader()->sortIndicatorOrder() == Qt::AscendingOrder);

    saveClientSettings(mw);

    clientMgr.saveUser(clientCfg);
    switchMgr();
    saveServerSettings(mw);
    switchMgr();
}

void SettingsMgr::loadClientSettings(Ui::MainWindow &mw)
{
    mw.leClientAddress->setText(QString::fromStdString(clientMgr.getString("destinationAddress", "General")));
    mw.leClientPort->setText(QString::fromStdString(clientMgr.getString("port", "General")));
    mw.leClientPassword->setText(QString::fromStdString(clientMgr.getString("password", "General")));
    mw.combLoglevel->setCurrentIndex(clientMgr.getInt("loglevel", "General"));

    mw.leClientMAddress->setText(QString::fromStdString(clientMgr.getString("address", "Master")));
    mw.leClientMPort->setText(QString::fromStdString(clientMgr.getString("port", "Master")));

    mw.pbChatKey->setText(QString::fromStdString(clientMgr.getString("keySay", "Chat")));
    mw.pbModeKey->setText(QString::fromStdString(clientMgr.getString("keyChatMode", "Chat")));

    mw.sbPosX->setValue(clientMgr.getInt("x", "Chat"));
    mw.sbPosY->setValue(clientMgr.getInt("y", "Chat"));
    mw.sbPosW->setValue(clientMgr.getInt("w", "Chat"));
    mw.sbPosH->setValue(clientMgr.getInt("h", "Chat"));

    mw.sbDelay->setValue(clientMgr.getFloat("delay", "Chat"));
}

void SettingsMgr::saveClientSettings(Ui::MainWindow &mw)
{
    clientMgr.setString("destinationAddress", "General", mw.leClientAddress->text().toStdString());
    clientMgr.setString("port", "General", mw.leClientPort->text().toStdString());
    clientMgr.setString("password", "General", mw.leClientPassword->text().toStdString());
    clientMgr.setInt("loglevel", "General", mw.combLoglevel->currentIndex());

    clientMgr.setString("address", "Master", mw.leClientMAddress->text().toStdString());
    clientMgr.setString("port", "Master", mw.leClientMPort->text().toStdString());

    clientMgr.setString("keySay", "Chat", mw.pbChatKey->text().toStdString());
    clientMgr.setString("keyChatMode", "Chat", mw.pbModeKey->text().toStdString());

    clientMgr.setInt("x", "Chat", mw.sbPosX->value());
    clientMgr.setInt("y", "Chat", mw.sbPosY->value());
    clientMgr.setInt("w", "Chat", mw.sbPosW->value());
    clientMgr.setInt("h", "Chat", mw.sbPosH->value());

    clientMgr.setFloat("delay", "Chat", mw.sbDelay->value());

}

void SettingsMgr::loadServerSettings(Ui::MainWindow &mw)
{
    mw.leServerAddress->setText(QString::fromStdString(serverMgr.getString("localAddress", "General")));
    mw.leServerPort->setText(QString::fromStdString(serverMgr.getString("port", "General")));
    mw.sbMaxPlayers->setValue(serverMgr.getInt("maximumPlayers", "General"));
    mw.leHostname->setText(QString::fromStdString(serverMgr.getString("hostname", "General")));
    mw.combServerLoglevel->setCurrentIndex(serverMgr.getInt("logLevel", "General"));
    mw.leServerPassword->setText(QString::fromStdString(serverMgr.getString("password", "General")));

    mw.chbMSenabled->setCheckState(serverMgr.getBool("enabled", "MasterServer") ? Qt::Checked : Qt::Unchecked);
    mw.leServerMaddress->setText(QString::fromStdString(serverMgr.getString("address", "MasterServer")));
    mw.leServerMPort->setText(QString::fromStdString(serverMgr.getString("port", "MasterServer")));
    mw.sbRate->setValue(serverMgr.getInt("rate", "MasterServer"));

#ifndef TES3MP_PRE07
    mw.leModulePath->setText(QString::fromStdString(serverMgr.getString("home", "Modules")));
    mw.chbAutosort->setCheckState(serverMgr.getBool("autoSort", "Modules") ? Qt::Checked : Qt::Unchecked);
#else
    mw.leModulePath->setText(QString::fromStdString(serverMgr.getString("home", "Plugins")));
#endif

}

void SettingsMgr::saveServerSettings(Ui::MainWindow &mw)
{
    serverMgr.setString("localAddress", "General", mw.leServerAddress->text().toStdString());
    serverMgr.setString("port", "General", mw.leServerPort->text().toStdString());
    serverMgr.setInt("maximumPlayers", "General", mw.sbMaxPlayers->value());
    serverMgr.setString("hostname", "General", mw.leHostname->text().toStdString());
    serverMgr.setInt("logLevel", "General", mw.combServerLoglevel->currentIndex());
    serverMgr.setString("password", "General", mw.leServerPassword->text().toStdString());

    serverMgr.setBool("enabled", "MasterServer", mw.chbMSenabled->checkState() == Qt::Checked);
    serverMgr.setString("address", "MasterServer", mw.leServerMaddress->text().toStdString());
    serverMgr.setString("port", "MasterServer", mw.leServerMPort->text().toStdString());
    serverMgr.setInt("rate", "MasterServer", mw.sbRate->value());

#ifndef TES3MP_PRE07
    serverMgr.setString("home", "Modules", mw.leModulePath->text().toStdString());
    serverMgr.setBool("autoSort", "Modules", mw.chbAutosort->checkState() == Qt::Checked);
#else
    serverMgr.setString("home", "Plugins", mw.leModulePath->text().toStdString());
#endif

    serverMgr.saveUser(serverCfg);
}

void SettingsMgr::switchMgr()
{
    static Settings::CategorySettingValueMap saveUserSettings;
    static Settings::CategorySettingValueMap saveDefaultSettings;
    static Settings::CategorySettingVector saveChangedSettings;
    static bool currentMgrIsClient = true;

    if(!currentMgrIsClient)
    {
        saveUserSettings.swap(clientMgr.mUserSettings);
        saveDefaultSettings.swap(clientMgr.mDefaultSettings);
        saveChangedSettings.swap(clientMgr.mChangedSettings);

        qDebug() << "Manager switched to Client config";
    }
    else
    {
        saveUserSettings.swap(serverMgr.mUserSettings);
        saveDefaultSettings.swap(serverMgr.mDefaultSettings);
        saveChangedSettings.swap(serverMgr.mChangedSettings);

        qDebug() << "Manager switched to Server config";
    }
    currentMgrIsClient = !currentMgrIsClient;
}
