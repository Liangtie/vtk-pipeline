#include <QFile>
#include <memory>

#include "vtkImageViewerDelegate.hpp"

#include <qtpreprocessorsupport.h>

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include "vtk_output/EmbeddedQVTKRenderWidget.hpp"
#include "vtk_shapes/vtk_shape.hpp"
#include "vtk_source/VtkAlgorithmOutputData.hpp"
#include "vtk_source/decimal/DecimalData.hpp"
#include "vtk_source/file_path/FilePathData.hpp"

enum
{
    ColorLevel,
    ColorWindow,
    InputConnection,
    InCount
};

constexpr auto kColorLevel = 138.5;

constexpr auto kColorWindow = 233.0;

vtkImageViewerDelegate::vtkImageViewerDelegate()
    : VtkShape(class_id)
    , _text(std::make_shared<FilePathData>(""))
    , _vtk_widget {nullptr}
{
    _image_view->SetColorLevel(kColorLevel);
    _image_view->SetColorWindow(kColorWindow);
}

QJsonObject vtkImageViewerDelegate::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();
    modelJson["ColorLevel"] = _image_view->GetColorLevel();
    modelJson["ColorWindow"] = _image_view->GetColorWindow();
    return modelJson;
}

void vtkImageViewerDelegate::load(QJsonObject const& p)
{
    {
        QJsonValue v = p["ColorLevel"];

        if (!v.isUndefined()) {
            QString str = v.toString();

            bool ok {};

            auto c = str.toDouble(&ok);

            if (ok) {
                _image_view->SetColorLevel(c);
            }
        }
    }
    {
        QJsonValue v = p["ColorWindow"];

        if (!v.isUndefined()) {
            QString str = v.toString();

            bool ok {};

            auto c = str.toDouble(&ok);

            if (ok) {
                _image_view->SetColorWindow(c);
            }
        }
    }
}

unsigned int vtkImageViewerDelegate::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
        case PortType::In:
            result = InCount;
            break;

        case PortType::Out:
            result = 0;

        default:
            break;
    }

    return result;
}

NodeDataType vtkImageViewerDelegate::dataType(PortType t, PortIndex idx) const
{
    switch (t) {
        case QtNodes::PortType::In:
            switch (idx) {
                case ColorLevel:
                    return DecimalData("ColorLevel").type();
                case ColorWindow:
                    return DecimalData("ColorWindow").type();
                case InputConnection:
                    return VtkAlgorithmOutputData().type();
            }
            break;
        case QtNodes::PortType::Out:
        case QtNodes::PortType::None:
            break;
    }
    return {};
}

QWidget* vtkImageViewerDelegate::embeddedWidget()
{
    if (!_vtk_widget) {
        _vtk_widget = new EmbeddedQVTKRenderWidget();
        _vtk_widget->setRenderWindow(_renWin);
    }
    return _vtk_widget;
}

void vtkImageViewerDelegate::setInData(std::shared_ptr<NodeData> data,
                                       PortIndex const portIndex)
{
    switch (portIndex) {
        case ColorLevel:
            if (auto d = std::dynamic_pointer_cast<DecimalData>(data))
                _image_view->SetColorLevel(d->number());
            break;
        case ColorWindow:
            if (auto d = std::dynamic_pointer_cast<DecimalData>(data))
                _image_view->SetColorWindow(d->number());
            break;
        case InputConnection:
            if (auto d =
                    std::dynamic_pointer_cast<VtkAlgorithmOutputData>(data))
            {
                _image_view->SetInputConnection(d->algorithmOutput());
                _image_view->SetRenderWindow(_renWin);
                _image_view->SetRenderWindow(_renWin);
                _image_view->SetupInteractor(_renWin->GetInteractor());
            } else {
                _image_view->SetInputConnection(nullptr);
                _image_view->RemoveAllObservers();
            }
            break;
    }
}
