#include "bottom_left_menu_view.hpp"

#include <qlistview.h>
BottomLeftMenuView::BottomLeftMenuView(QWidget* parent, int item_size)
    : QListView(parent)
    , _item_size(item_size)
{
}

BottomLeftMenuView::~BottomLeftMenuView() = default;

QSize BottomLeftMenuView::sizeHint() const
{
    if (model()->rowCount() == 0)
        return {width(), 0};
    return {
        width(),
        (_item_size < model()->rowCount() ? _item_size : model()->rowCount())
            * sizeHintForRow(0)};
}

void BottomLeftMenuView::wheelEvent(QWheelEvent* e)
{
    e->ignore();
}