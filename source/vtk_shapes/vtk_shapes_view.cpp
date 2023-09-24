#include <QIcon>
#include <QToolButton>

#include "vtk_shapes_view.hpp"

#include <qheaderview.h>
#include <qicon.h>
#include <qnamespace.h>
#include <qtreeview.h>

VtkShapesView::VtkShapesView(QWidget* parent)
    : QTreeView(parent)
{
    header()->setVisible(false);
    setRootIsDecorated(false);
}

void VtkShapesView::drawRow(QPainter* painter,
                            const QStyleOptionViewItem& options,
                            const QModelIndex& index) const
{
    QTreeView::drawRow(painter, options, index);

    enum
    {
        WIDTH = 12,
        HEIGHT = WIDTH
    };
    if (model()->hasChildren(index) || !model()->parent(index).isValid()) {
        if (isExpanded(index)) {
            static QIcon down(":/style/icon/down.png");
            down.paint(painter,
                       QRect(options.rect.topRight().x() - 2 * WIDTH,
                             options.rect.topRight().y()
                                 + (options.rect.height() - HEIGHT) / 2,
                             WIDTH,
                             HEIGHT),
                       Qt::AlignRight);
        } else {
            static QIcon right(":/style/icon/right.png");
            right.paint(painter,
                        QRect(options.rect.topRight().x() - 2 * WIDTH,
                              options.rect.topRight().y()
                                  + (options.rect.height() - HEIGHT) / 2,
                              WIDTH,
                              HEIGHT),
                        Qt::AlignRight);
        }
    }
}

VtkShapesView::~VtkShapesView() = default;
