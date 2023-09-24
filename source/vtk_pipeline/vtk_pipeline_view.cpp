#include <QOpenGLWidget>

#include "vtk_pipeline_view.hpp"

#include <qgraphicsview.h>

#include <QtOpenGLWidgets/QOpenGLWidget>

#include "QtNodes/internal/GraphicsView.hpp"
VtkPipelineView::VtkPipelineView(QWidget* parent)
    : VtkPipelineView(nullptr, parent)
{
}

VtkPipelineView::VtkPipelineView(BasicGraphicsScene* scene, QWidget* parent)
    : GraphicsView(scene, parent)
{
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setCacheMode(QGraphicsView::CacheNone);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

VtkPipelineView::~VtkPipelineView() {}
