//
// Created by koncord on 30.01.17.
//

#include "MySortFilterProxyModel.hpp"
#include "ServerModel.hpp"

#include <qdebug.h>
#include <apps/browser/netutils/Utils.hpp>

bool MySortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{

    QModelIndex pingIndex = sourceModel()->index(sourceRow, ServerData::PING, sourceParent);
    QModelIndex plIndex = sourceModel()->index(sourceRow, ServerData::PLAYERS, sourceParent);
    QModelIndex maxPlIndex = sourceModel()->index(sourceRow, ServerData::MAX_PLAYERS, sourceParent);

    int ping = sourceModel()->data(pingIndex).toInt();
    int players =  sourceModel()->data(plIndex).toInt();
    int maxPlayers =  sourceModel()->data(maxPlIndex).toInt();

    if (maxPing > 0 && (ping == -1 || ping > maxPing))
        return false;
    if (filterEmpty && players == 0)
        return false;
    if (filterFull && players >= maxPlayers)
        return false;

    return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
}

bool MySortFilterProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    if(sortColumn() == ServerData::PING)
    {
        bool valid;
        QModelIndex cLeft = source_left;
        QModelIndex cRight = source_right;

        int pingright = sourceModel()->data(source_right).toInt(&valid);
        pingright = valid ? pingright : PING_UNREACHABLE;

        int pingleft = sourceModel()->data(source_left).toInt(&valid);
        pingleft = valid ? pingleft : PING_UNREACHABLE;
        return pingleft < pingright;
    }
    else
        return QSortFilterProxyModel::lessThan(source_left, source_right);
}

MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    filterEmpty = false;
    filterFull = false;
    maxPing = 0;
    setSortCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
}

void MySortFilterProxyModel::filterEmptyServers(bool state)
{
    filterEmpty = state;
    invalidateFilter();
}

void MySortFilterProxyModel::filterFullServer(bool state)
{
    filterFull = state;
    invalidateFilter();
}

void MySortFilterProxyModel::pingLessThan(int maxPing)
{
    this->maxPing = maxPing;
    invalidateFilter();
}
