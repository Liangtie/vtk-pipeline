#pragma once

#include <utility>

#include <qcolor.h>
#include <vtkMapper.h>

#include <QtNodes/NodeData>
using QtNodes::NodeData;
using QtNodes::NodeDataType;
class vtkMapperData : public NodeData
{
  public:
    vtkMapperData() = default;

    vtkMapperData(vtkMapper* c)
        : _value(c)
    {
    }
    [[nodiscard]] NodeDataType type() const override
    {
        return NodeDataType {"mapper", "mapper"};
    }

    [[nodiscard]] auto getValue() const { return _value; }

    auto setValue(vtkMapper* c) { _value = c; }

  private:
    vtkMapper* _value;
};
