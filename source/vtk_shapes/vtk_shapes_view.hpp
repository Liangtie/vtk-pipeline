#ifndef VTK_SHAPES_VIEW_HPP
#define VTK_SHAPES_VIEW_HPP

#include <QTreeView>

#include <qtreeview.h>
#include <qwidget.h>
class VtkShapesView : public QTreeView
{
  public:
    VtkShapesView(QWidget* parent = nullptr);

    ~VtkShapesView() override;

  protected:
    void drawRow(QPainter* painter,
                 const QStyleOptionViewItem& options,
                 const QModelIndex& index) const override;
};

#endif