#include <QIcon>

#include "bottom_left_menu_model.hpp"

#include <qicon.h>
#include <qnamespace.h>
#include <qvariant.h>
BottomLeftMenuModel::BottomLeftMenuModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int BottomLeftMenuModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return ROWS::ROW_COUNT;
}

QVariant BottomLeftMenuModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return {};

    switch (role) {
        case Qt::TextAlignmentRole:
            return QVariant::fromValue(Qt::AlignLeft | Qt::AlignVCenter);
        case Qt::DisplayRole:
        case Qt::EditRole:

            switch (index.row()) {
                case ABOUT:
                    return "About";
                case SETTINGS:
                    return "Settings";
            }

        case Qt::DecorationRole:

            switch (index.row()) {
                case ABOUT:
                    return QIcon(":/style/icon/about.png");
                case SETTINGS:
                    return QIcon(":/style/icon/settings.png");
            }
            break;
    }

    return {};
}
