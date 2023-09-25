#include <QFile>
#include <memory>

#include "vtkActorDelegate.hpp"

#include <qcolor.h>
#include <qrgb.h>

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QtWidgets/QLineEdit>

#include "vtkActorDelegate.hpp"
#include "vtk_shapes/vtk_shape.hpp"
#include "vtk_source/VtkAlgorithmOutputData.hpp"
#include "vtk_source/decimal/DecimalData.hpp"

enum
{
    COLOR,
    SRC,

    INPUT_COUNT,
};

vtkActorDelegate::vtkActorDelegate()
    : VtkShape(class_id)
{
}

vtkActorDelegate::~vtkActorDelegate() {}

QJsonObject vtkActorDelegate::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();
    modelJson["_color"] = static_cast<int>(_color.rgb());
    return modelJson;
}

void vtkActorDelegate::load(QJsonObject const& p)
{
    {
        QJsonValue v = p["_color"];

        if (!v.isUndefined()) {
            _color = QColor(v.toInt());
        }
    }
}

unsigned int vtkActorDelegate::nPorts(PortType portType) const
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

NodeDataType vtkActorDelegate::dataType(PortType t, PortIndex idx) const
{
    switch (t) {
        case QtNodes::PortType::In:
            switch (idx) {
                case COLOR:
                    return VtkAlgorithmOutputData().type();
                case SRC:
                    return VtkAlgorithmOutputData().type();
            }
        case QtNodes::PortType::Out:
            return VtkAlgorithmOutputData().type();

        case QtNodes::PortType::None:
            break;
    }

    return {};
}

std::shared_ptr<NodeData> vtkActorDelegate::outData(PortIndex)
{
    if (_filter->GetInput())
        _filter->Update();
    return std::make_shared<VtkAlgorithmOutputData>(_filter->GetOutputPort());
}

void vtkActorDelegate::setInData(std::shared_ptr<NodeData> data, PortIndex)
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

QWidget* vtkActorDelegate::embeddedWidget()
{
    return {};
}
