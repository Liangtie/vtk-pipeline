#include "bottom_left_menu_view.hpp"

#include <qlistview.h>
BottomLeftMenuView::BottomLeftMenuView(int item_size, QWidget* parent)
    : QListView(parent)
    , _item_size(item_size)
{
}

BottomLeftMenuView::~BottomLeftMenuView() = default;

// QSize BottomLeftMenuView::sizeHint() const
// {
//     if (model()->rowCount() == 0)
//         return {width(), 0};
//     int nToShow =
//         _item_size < model()->rowCount() ? _item_size : model()->rowCount();
//     return {width(), nToShow * sizeHintForRow(0)};
// }