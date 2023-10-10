#include <QFile>
#include <memory>

#include "vtkOutlineFilterDelegate.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QtWidgets/QLineEdit>

#include "vtk_shapes/vtk_shape.hpp"
#include "vtk_source/VtkAlgorithmOutputData.hpp"
#include "vtk_source/decimal/DecimalData.hpp"

enum
{
    SRC,

    INPUT_COUNT,
};

vtkOutlineFilterDelegate::vtkOutlineFilterDelegate()
    : VtkShape(class_id)
{

}

vtkOutlineFilterDelegate::~vtkOutlineFilterDelegate() {}

QJsonObject vtkOutlineFilterDelegate::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();
    return modelJson;
}

void vtkOutlineFilterDelegate::load(QJsonObject const& p)
{

}

unsigned int vtkOutlineFilterDelegate::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
        case PortType::In:
            result = INPUT_COUNT;
            break;
        case PortType::Out:
            result = 1;
        default:
            break;
    }

    return result;
}

NodeDataType vtkOutlineFilterDelegate::dataType(PortType, PortIndex) const
{
    return VtkAlgorithmOutputData().type();
}

std::shared_ptr<NodeData> vtkOutlineFilterDelegate::outData(PortIndex)
{
    if (_filter->GetInput())
        _filter->Update();
    return std::make_shared<VtkAlgorithmOutputData>(_filter->GetOutputPort());
}

void vtkOutlineFilterDelegate::setInData(std::shared_ptr<NodeData> data,
                                         PortIndex)
{
    _filter = vtkNew<vtkOutlineFilter>();
    if (auto d = std::dynamic_pointer_cast<VtkAlgorithmOutputData>(data))
        _filter->SetInputConnection(d->algorithmOutput());
    _filter->SetInputConnection(_last_in);
    if (_last_in) {
        Q_EMIT dataUpdated(0);
    } else {
        Q_EMIT dataInvalidated(0);
    }
}

QWidget* vtkOutlineFilterDelegate::embeddedWidget()
{
    return {};
}
