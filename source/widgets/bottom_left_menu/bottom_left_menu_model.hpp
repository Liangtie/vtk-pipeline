#ifndef BOTTOM_LEFT_MENU_MODEL_HPP
#define BOTTOM_LEFT_MENU_MODEL_HPP
#include <QAbstractListModel>

class BottomLeftMenuModel : public QAbstractListModel
{
    Q_OBJECT

  public:
    enum ROWS
    {
        ABOUT,
        SETTINGS,
        ROW_COUNT
    };

    explicit BottomLeftMenuModel(QObject* parent = nullptr);

    // Basic functionality:
    [[nodiscard]] int rowCount(
        const QModelIndex& parent = QModelIndex()) const override;

    [[nodiscard]] QVariant data(const QModelIndex& index,
                                int role = Qt::DisplayRole) const override;

  private:
};


#endif