#pragma once

#include <utility>

#include <qcolor.h>
#include <vtkActor.h>
#include <vtkRenderer.h>

#include <QtNodes/NodeData>
using QtNodes::NodeData;
using QtNodes::NodeDataType;
class vtkRendererData : public NodeData
{
  public:
    vtkRendererData() = default;

    vtkRendererData(vtkRenderer* c)
        : _value(c)
    {
    }
    [[nodiscard]] NodeDataType type() const override
    {
        return NodeDataType {"renderer", "renderer"};
    }

    [[nodiscard]] auto getValue() const { return _value; }

    auto setValue(vtkRenderer* c) { _value = c; }

  private:
    vtkRenderer* _value;
};
