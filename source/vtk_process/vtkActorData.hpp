#pragma once

#include <utility>

#include <qcolor.h>
#include <vtkActor.h>

#include <QtNodes/NodeData>
using QtNodes::NodeData;
using QtNodes::NodeDataType;
class vtkActorData : public NodeData
{
  public:
    vtkActorData() = default;

    vtkActorData(vtkActor* c)
        : _value(c)
    {
    }
    [[nodiscard]] NodeDataType type() const override
    {
        return NodeDataType {"actor", "actor"};
    }

    [[nodiscard]] auto getActor() const { return _value; }

    auto setActor(vtkActor* c) { _value = c; }

  private:
    vtkActor* _value;
};
