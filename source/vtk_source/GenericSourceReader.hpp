#ifndef GENERICSOURCEREADER_HPP
#define GENERICSOURCEREADER_HPP
#include <iostream>
#include <memory>

#include <QtCore/QObject>
#include <QtNodes/NodeDelegateModel>
#include <QtNodes/NodeDelegateModelRegistry>
#include <QtWidgets/QLabel>

#include "vtk_shapes/vtk_shape.hpp"

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;
class GenericSourceReader
    : public NodeDelegateModel
    , public VtkShape
{
  public:
    GenericSourceReader(QString id)
        : NodeDelegateModel()
        , VtkShape(id)
    {
    }

    [[nodiscard]] unsigned int nPorts(PortType portType) const override
    {
        unsigned int result = 1;

        switch (portType) {
            case PortType::In:
                result = 1;
                break;

            case PortType::Out:
                result = 1;

            default:
                break;
        }

        return result;
    }
    [[nodiscard]] bool resizable() const override { return true; }
};

#endif