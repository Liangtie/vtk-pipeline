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
};

#endif