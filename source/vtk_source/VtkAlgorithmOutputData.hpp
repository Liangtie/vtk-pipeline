#ifndef VTKALGORITHMOUTPUTDATA_HPP
#define VTKALGORITHMOUTPUTDATA_HPP

#include <utility>

#include <vtkAlgorithmOutput.h>

#include <QtNodes/NodeData>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

class VtkAlgorithmOutputData : public NodeData
{
  public:
    VtkAlgorithmOutputData() = default;

    VtkAlgorithmOutputData(vtkAlgorithmOutput* out)
        : _algorithmOutput(out)
    {
    }

    [[nodiscard]] NodeDataType type() const override
    {
        return NodeDataType {"vtkAlgorithmOutput", "vtkAlgorithmOutput"};
    }

    [[nodiscard]] vtkAlgorithmOutput* algorithmOutput() const
    {
        return _algorithmOutput;
    }

  private:
    vtkAlgorithmOutput* _algorithmOutput;
};

#endif