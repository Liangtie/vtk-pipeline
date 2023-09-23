#ifndef VTK_PIPELINE_SCENE_HPP
#define VTK_PIPELINE_SCENE_HPP

#include "QtNodes/DataFlowGraphicsScene"

using QtNodes::DataFlowGraphicsScene;
using QtNodes::DataFlowGraphModel;
class VtkPipelineScene : public DataFlowGraphicsScene
{
  public:
    VtkPipelineScene(DataFlowGraphModel& graphModel, QObject* parent = nullptr);
    ~VtkPipelineScene() override;
};

#endif