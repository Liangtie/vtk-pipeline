#include <QFile>
#include <memory>

#include "vtkPolyDataMapperDelegate.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QtWidgets/QLineEdit>

#include "vtkPolyDataMapperDelegate.hpp"
#include "vtk_mapper/vtkMapperData.hpp"
#include "vtk_shapes/vtk_shape.hpp"
#include "vtk_source/VtkAlgorithmOutputData.hpp"
#include "vtk_source/decimal/DecimalData.hpp"

enum
{
    SRC,

    INPUT_COUNT,
};

vtkPolyDataMapperDelegate::vtkPolyDataMapperDelegate()
    : VtkShape(class_id)
{
}

vtkPolyDataMapperDelegate::~vtkPolyDataMapperDelegate() {}

QJsonObject vtkPolyDataMapperDelegate::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();

    modelJson["_featureAngle"] = _featureAngle;

    return modelJson;
}

void vtkPolyDataMapperDelegate::load(QJsonObject const& p)
{
    {
        QJsonValue v = p["_featureAngle"];

        if (!v.isUndefined()) {
            _featureAngle = v.toDouble();
        }
    }
}

unsigned int vtkPolyDataMapperDelegate::nPorts(PortType portType) const
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

NodeDataType vtkPolyDataMapperDelegate::dataType(PortType t, PortIndex) const
{
    switch (t) {
        case QtNodes::PortType::In:
            return VtkAlgorithmOutputData().type();
        case QtNodes::PortType::Out:
            return vtkMapperData().type();
        case QtNodes::PortType::None:
            break;
    }
    return {};
}

std::shared_ptr<NodeData> vtkPolyDataMapperDelegate::outData(PortIndex)
{
    if (_filter->GetInput())
        _filter->Update();
    return std::make_shared<vtkMapperData>(_filter);
}

void vtkPolyDataMapperDelegate::setInData(std::shared_ptr<NodeData> data,
                                          PortIndex)
{
    _filter = vtkNew<vtkPolyDataMapper>();
    if (auto d = std::dynamic_pointer_cast<VtkAlgorithmOutputData>(data))
        _filter->SetInputConnection(d->algorithmOutput());
    _filter->SetInputConnection(_last_in);
    _filter->ScalarVisibilityOff();
    if (_last_in) {
        Q_EMIT dataUpdated(0);
    } else {
        Q_EMIT dataInvalidated(0);
    }
}

QWidget* vtkPolyDataMapperDelegate::embeddedWidget()
{
    return {};
}
