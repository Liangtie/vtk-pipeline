#include <memory>

#include "vtkPNGReaderDelegate.hpp"

#include <qtpreprocessorsupport.h>

#include <QtCore/QDir>
#include <QtCore/QEvent>
#include <QtWidgets/QFileDialog>

#include "FilePathData.hpp"
#include "VtkAlgorithmOutputData.hpp"
#include "vtk_shapes/vtk_shape.hpp"
#include "vtk_source/FilePathData.hpp"
#include "vtk_source/vtkAlgorithmOutputData.hpp"

vtkPNGReaderDelegate::vtkPNGReaderDelegate()
    : VtkShape(class_id)
    , _reader({})
{
}

vtkPNGReaderDelegate::~vtkPNGReaderDelegate() {}

QJsonObject vtkPNGReaderDelegate::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();

    modelJson["png_path"] = _reader->GetFileName();

    return modelJson;
}

void vtkPNGReaderDelegate::load(QJsonObject const& p)
{
    QJsonValue v = p["png_path"];

    if (!v.isUndefined()) {
        QString str = v.toString();

        if (QFile::exists(str)
            && _reader->CanReadFile(str.toStdString().c_str()))
        {
            _reader->SetFileName(str.toStdString().c_str());
        }
    }
}

unsigned int vtkPNGReaderDelegate::nPorts(PortType portType) const
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

NodeDataType vtkPNGReaderDelegate::dataType(PortType const t,
                                            PortIndex const) const
{
    switch (t) {
        case QtNodes::PortType::In:
            return FilePathData().type();
        case QtNodes::PortType::Out:
            return VtkAlgorithmOutputData().type();
            break;
        case QtNodes::PortType::None:
            break;
    }
    return {};
}

std::shared_ptr<NodeData> vtkPNGReaderDelegate::outData(PortIndex idx)
{
    Q_UNUSED(idx)
    return std::make_shared<VtkAlgorithmOutputData>(_reader->GetOutputPort());
}

void vtkPNGReaderDelegate::setInData(std::shared_ptr<NodeData> data,
                                     PortIndex const portIndex)
{
    Q_UNUSED(portIndex)

    if (auto fp = std::dynamic_pointer_cast<FilePathData>(data);
        _reader->CanReadFile(fp->filePath().toStdString().data()))
    {
        _reader->SetFileName(fp->filePath().toStdString().data());
        Q_EMIT dataUpdated(0);

    } else {
        Q_EMIT dataInvalidated(0);
    }
}
