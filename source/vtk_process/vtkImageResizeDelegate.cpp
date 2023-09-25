#include <QFile>
#include <memory>

#include "vtkImageResizeDelegate.hpp"

#include <vtkAlgorithmOutput.h>

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QtWidgets/QLineEdit>

#include "vtkImageResizeDelegate.hpp"
#include "vtk_shapes/vtk_shape.hpp"
#include "vtk_source/VtkAlgorithmOutputData.hpp"
#include "vtk_source/decimal/DecimalData.hpp"
enum
{
    x,
    y,
    z,
    src,

    COUNT
};

vtkImageResizeDelegate::vtkImageResizeDelegate()
    : VtkShape(class_id)
{
    _image_resize->SetOutputDimensions(-1, -1, -1);
}

vtkImageResizeDelegate::~vtkImageResizeDelegate() {}

QJsonObject vtkImageResizeDelegate::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();
    auto dd = _image_resize->GetOutputDimensions();
    modelJson["x"] = dd[0];
    modelJson["y"] = dd[1];
    modelJson["z"] = dd[2];
    return modelJson;
}

void vtkImageResizeDelegate::load(QJsonObject const& p)
{
    int x = -1, y = -1, z = -1;

    {
        QJsonValue v = p["x"];
        if (!v.isUndefined()) {
            QString str = v.toString();
            bool ok {};
            auto res = str.toInt(&ok);
            if (ok) {
                x = res;
            }
        }
    }

    {
        QJsonValue v = p["y"];
        if (!v.isUndefined()) {
            QString str = v.toString();
            bool ok {};
            auto res = str.toInt(&ok);
            if (ok) {
                y = res;
            }
        }
    }

    {
        QJsonValue v = p["z"];
        if (!v.isUndefined()) {
            QString str = v.toString();
            bool ok {};
            auto res = str.toInt(&ok);
            if (ok) {
                z = res;
            }
        }
    }

    _image_resize->SetOutputDimensions(x, y, z);
}

unsigned int vtkImageResizeDelegate::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
        case PortType::In:
            result = COUNT;
            break;
        case PortType::Out:
            result = 1;
        default:
            break;
    }

    return result;
}

NodeDataType vtkImageResizeDelegate::dataType(PortType t, PortIndex idx) const
{
    switch (t) {
        case QtNodes::PortType::In:
            switch (idx) {
                case x:
                    return DecimalData("x").type();
                case y:
                    return DecimalData("y").type();
                case z:
                    return DecimalData("z").type();
                case src:
                    return VtkAlgorithmOutputData().type();
            }
            break;
        case QtNodes::PortType::Out:
            return VtkAlgorithmOutputData().type();
        case QtNodes::PortType::None:
            break;
    }
}

std::shared_ptr<NodeData> vtkImageResizeDelegate::outData(PortIndex)
{
    _image_resize->Update();
    return std::make_shared<VtkAlgorithmOutputData>(
        _image_resize->GetOutputPort());
}

void vtkImageResizeDelegate::setInData(std::shared_ptr<NodeData> data,
                                       PortIndex idx)
{
    auto old = _image_resize->GetOutputDimensions();
    switch (idx) {
        case x:
            if (auto d = std::dynamic_pointer_cast<DecimalData>(data))
                old[x] = static_cast<int>(d->number());
            break;
        case y:
            if (auto d = std::dynamic_pointer_cast<DecimalData>(data))
                old[y] = static_cast<int>(d->number());
            break;
        case z:
            if (auto d = std::dynamic_pointer_cast<DecimalData>(data))
                old[z] = static_cast<int>(d->number());
            break;
        case src:
            if (auto d =
                    std::dynamic_pointer_cast<VtkAlgorithmOutputData>(data))
                _image_resize->SetInputConnection(d->algorithmOutput());
            break;
    }
    _image_resize->SetOutputDimensions(old[x], old[y], old[z]);
    Q_EMIT dataUpdated(0);
}

QWidget* vtkImageResizeDelegate::embeddedWidget()
{
    return {};
}
