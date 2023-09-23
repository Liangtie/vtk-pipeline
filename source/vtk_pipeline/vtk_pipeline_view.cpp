#include "vtk_pipeline_view.hpp"

#include "QtNodes/internal/GraphicsView.hpp"
VtkPipelineView::VtkPipelineView(QWidget* parent)
    : VtkPipelineView(nullptr, parent)
{
}

VtkPipelineView::VtkPipelineView(BasicGraphicsScene* scene, QWidget* parent)
    : GraphicsView(scene, parent)
{
}

VtkPipelineView::~VtkPipelineView() {}
