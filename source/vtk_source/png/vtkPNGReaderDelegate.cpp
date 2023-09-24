#include <memory>

#include "vtkPNGReaderDelegate.hpp"

#include <qtpreprocessorsupport.h>

#include <QtCore/QDir>
#include <QtCore/QEvent>
#include <QtWidgets/QFileDialog>

#include "vtk_source/VtkAlgorithmOutputData.hpp"
#include "vtk_source/file_path/FilePathData.hpp"
#include "vtk_source/vtkAlgorithmOutputData.hpp"

vtkPNGReaderDelegate::vtkPNGReaderDelegate()
    : GenericSourceReader(class_id)
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
        fp && _reader->CanReadFile(fp->filePath().toStdString().data()))
    {
        _reader->SetFileName(fp->filePath().toStdString().data());

        Q_EMIT dataUpdated(0);

    } else {
        Q_EMIT dataInvalidated(0);
    }
}
