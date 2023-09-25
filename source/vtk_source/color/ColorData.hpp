#pragma once

#include <utility>

#include <qcolor.h>

#include <QtNodes/NodeData>
using QtNodes::NodeData;
using QtNodes::NodeDataType;
class ColorData : public NodeData
{
  public:
    ColorData() = default;

    ColorData(QColor c)
        : _color(std::move(c))
    {
    }
    [[nodiscard]] NodeDataType type() const override
    {
        return NodeDataType {"color", "color"};
    }

    [[nodiscard]] auto getColor() const { return _color; }

    auto setColor(QColor c) { _color = c; }

  private:
    QColor _color;
};
