#include <QFile>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <memory>

#include "vtkGenericOpenGLRenderWindowDelegate.hpp"

#include <qtpreprocessorsupport.h>
#include <vtkCamera.h>
#include <vtkGLTFImporter.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkLight.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>

#include "vtkGenericOpenGLRenderWindowDelegate.hpp"
#include "vtk_output/EmbeddedQVTKRenderWidget.hpp"
#include "vtk_process/vtkRendererData.hpp"
#include "vtk_shapes/vtk_shape.hpp"
#include "vtk_source/VtkAlgorithmOutputData.hpp"
#include "vtk_source/decimal/DecimalData.hpp"
#include "vtk_source/file_path/FilePathData.hpp"

vtkGenericOpenGLRenderWindowDelegate::vtkGenericOpenGLRenderWindowDelegate()
    : VtkShape(class_id)
    , _vtk_widget {nullptr}
{
}
vtkGenericOpenGLRenderWindowDelegate::~vtkGenericOpenGLRenderWindowDelegate()
{
    // _renderWindowInteractor->Disable();
    _renWin->Finalize();
    if (_vtk_widget)
        _vtk_widget->close();
}

QJsonObject vtkGenericOpenGLRenderWindowDelegate::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();
    // modelJson["FileName"] = _gLTFImporter->GetFileName();
    return modelJson;
}

void vtkGenericOpenGLRenderWindowDelegate::load(QJsonObject const& p) {}

unsigned int vtkGenericOpenGLRenderWindowDelegate::nPorts(
    PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
        case PortType::In:
            result = 1;
            break;

        case PortType::Out:
            result = 0;

        default:
            break;
    }

    return result;
}

NodeDataType vtkGenericOpenGLRenderWindowDelegate::dataType(PortType t,
                                                            PortIndex) const
{
    switch (t) {
        case QtNodes::PortType::In:
            return vtkRendererData().type();
        case QtNodes::PortType::Out:
        case QtNodes::PortType::None:
            break;
    }
    return {};
}

QWidget* vtkGenericOpenGLRenderWindowDelegate::embeddedWidget()
{
    if (!_vtk_widget) {
        _vtk_widget = new EmbeddedQVTKRenderWidget();
    }
    return _vtk_widget;
}

void vtkGenericOpenGLRenderWindowDelegate::setInData(
    std::shared_ptr<NodeData> data, PortIndex const)
{
    if (auto fp = std::dynamic_pointer_cast<vtkRendererData>(data)) {
        if (_vtk_widget) {
            _renWin = vtkNew<vtkGenericOpenGLRenderWindow>();
            _vtk_widget->setRenderWindow(_renWin);
            _renWin->AddRenderer(fp->getValue());
            // _renderWindowInteractor = vtkNew<vtkRenderWindowInteractor>();
            // _renderWindowInteractor->SetRenderWindow(_renWin);
            _renWin->Render();
            // _renderWindowInteractor->Start();
        }
    }
    if (_vtk_widget)
        if (auto item = dynamic_cast<QGraphicsObject*>(_vtk_widget->parent())) {
            if (auto scene = item->scene())
                scene->update();
        }
}
