#include <QFile>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <memory>

#include "vtkGLTFImporterDelegate.hpp"

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

#include "vtk_output/EmbeddedQVTKRenderWidget.hpp"
#include "vtk_shapes/vtk_shape.hpp"
#include "vtk_source/VtkAlgorithmOutputData.hpp"
#include "vtk_source/decimal/DecimalData.hpp"
#include "vtk_source/file_path/FilePathData.hpp"

constexpr auto kColorLevel = 138.5;

constexpr auto kColorWindow = 233.0;

vtkGLTFImporterDelegate::vtkGLTFImporterDelegate()
    : VtkShape(class_id)
    , _vtk_widget {nullptr}
{
}
vtkGLTFImporterDelegate::~vtkGLTFImporterDelegate()
{
    _renderWindowInteractor.Reset();
    _renderer.Reset();
}

QJsonObject vtkGLTFImporterDelegate::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();
    modelJson["FileName"] = _gLTFImporter->GetFileName();
    return modelJson;
}

void vtkGLTFImporterDelegate::load(QJsonObject const& p)
{
    {
        QJsonValue v = p["FileName"];

        if (!v.isUndefined()) {
            QString str = v.toString();
            _gLTFImporter->SetFileName(str.toStdString().c_str());
        }
    }
}

unsigned int vtkGLTFImporterDelegate::nPorts(PortType portType) const
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

NodeDataType vtkGLTFImporterDelegate::dataType(PortType t, PortIndex idx) const
{
    switch (t) {
        case QtNodes::PortType::In:
            return FilePathData().type();
        case QtNodes::PortType::Out:
        case QtNodes::PortType::None:
            break;
    }
    return {};
}

QWidget* vtkGLTFImporterDelegate::embeddedWidget()
{
    if (!_vtk_widget) {
        _vtk_widget = new EmbeddedQVTKRenderWidget();
    }
    return _vtk_widget;
}

void vtkGLTFImporterDelegate::init()
{
    _gLTFImporter->SetRenderWindow(_renWin);
    _vtk_widget->setRenderWindow(_renWin);
    vtkNew<vtkNamedColors> colors;
    vtkColor3d backgroundColor = colors->GetColor3d("SlateGray");
    _renderer->SetBackground(backgroundColor.GetData());
    _renderer->UseHiddenLineRemovalOn();
    _renWin->AddRenderer(_renderer);
    _renderWindowInteractor->SetRenderWindow(_renWin);
    _renderWindowInteractor->SetInteractorStyle(_style);
    _gLTFImporter->SetRenderWindow(_renWin);
    _headLight->SetLightTypeToHeadlight();
    _headLight->SwitchOn();
    _renderer->AddLight(_headLight);
}

void vtkGLTFImporterDelegate::setInData(std::shared_ptr<NodeData> data,
                                        PortIndex const)
{
    if (auto fp = std::dynamic_pointer_cast<FilePathData>(data)) {
        _gLTFImporter->SetFileName(fp->filePath().toStdString().c_str());
        _gLTFImporter->Update();
        if (_renWin) {
            if (!_initiated) {
                init();
                _initiated = true;
            }
            _gLTFImporter->SetRenderWindow(_renWin);
            _gLTFImporter->Update();
            _renWin->Render();
            _renderer->ResetCamera();
            _renderer->GetActiveCamera()->Azimuth(20);
            _renderer->GetActiveCamera()->Elevation(30);
            _renderer->ResetCameraClippingRange();
            _renWin->Render();
            _renderWindowInteractor->Start();
        }
    }

    if (auto item = dynamic_cast<QGraphicsObject*>(_vtk_widget->parent())) {
        if (auto scene = item->scene())
            scene->update();
    }
}
