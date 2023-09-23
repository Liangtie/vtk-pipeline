#include "vtk_pipeline_scene.hpp"

#include "QtNodes/internal/DataFlowGraphicsScene.hpp"
VtkPipelineScene::VtkPipelineScene(DataFlowGraphModel& graphModel,
                                   QObject* parent)
    : DataFlowGraphicsScene(graphModel, parent)
{
}

VtkPipelineScene::~VtkPipelineScene() = default;
