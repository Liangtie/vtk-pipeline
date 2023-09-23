#ifndef VTK_PIPELINE_VIEW_HPP
#define VTK_PIPELINE_VIEW_HPP
#include "QtNodes/GraphicsView"

using QtNodes::BasicGraphicsScene;
using QtNodes::GraphicsView;
class VtkPipelineView : public GraphicsView
{
  public:
    VtkPipelineView(QWidget* parent = Q_NULLPTR);
    VtkPipelineView(BasicGraphicsScene* scene, QWidget* parent = Q_NULLPTR);
    ~VtkPipelineView() override;
};

#endif