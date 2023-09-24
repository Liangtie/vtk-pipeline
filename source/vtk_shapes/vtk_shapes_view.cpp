#include "vtk_shapes_view.hpp"

#include <qheaderview.h>
#include <qtreeview.h>

VtkShapesView::VtkShapesView(QWidget* parent)
    : QTreeView(parent)
{
    header()->setVisible(false);
    setRootIsDecorated(false);
}

VtkShapesView::~VtkShapesView() = default;
