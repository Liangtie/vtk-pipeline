#ifndef BOTTOM_LEFT_MENU_VIEW_HPP
#define BOTTOM_LEFT_MENU_VIEW_HPP

#include <qlistview.h>
#include <qsize.h>
#include <qwidget.h>
class BottomLeftMenuView : public QListView
{
  public:
    BottomLeftMenuView(int item_size = 0, QWidget* parent = nullptr);
    ~BottomLeftMenuView() override;
    // [[nodiscard]] QSize sizeHint() const override;

  private:
    const int _item_size;
};

#endif