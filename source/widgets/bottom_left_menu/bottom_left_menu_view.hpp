#ifndef BOTTOM_LEFT_MENU_VIEW_HPP
#define BOTTOM_LEFT_MENU_VIEW_HPP

#include <qevent.h>
#include <qlistview.h>
#include <qsize.h>
#include <qwidget.h>
class BottomLeftMenuView : public QListView
{
  public:
    BottomLeftMenuView(QWidget* parent = nullptr, int item_size = 0);
    ~BottomLeftMenuView() override;
    [[nodiscard]] QSize sizeHint() const override;

  protected:
    void wheelEvent(QWheelEvent* e) override;

  private:
    const int _item_size;
};

#endif