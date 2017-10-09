//
// Created by koncord on 07.01.17.
//

#ifndef NEWLAUNCHER_SERVERINFODIALOG_HPP
#define NEWLAUNCHER_SERVERINFODIALOG_HPP

#include "ui_ServerInfo.h"

class ServerInfoDialog : public QDialog,  public Ui::Dialog
{
    Q_OBJECT
public:
    explicit ServerInfoDialog(QWidget *parent = nullptr);
    void Server(const QString &addr);
public slots:
    bool refresh();
private:
    QString addr;
};


#endif //NEWLAUNCHER_SERVERINFODIALOG_HPP
