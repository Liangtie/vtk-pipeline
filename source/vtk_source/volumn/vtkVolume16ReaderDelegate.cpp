#include <memory>

#include "vtkVolume16ReaderDelegate.hpp"

#include <qtpreprocessorsupport.h>

#include <QtCore/QDir>
#include <QtCore/QEvent>
#include <QtWidgets/QFileDialog>

#include "vtk_source/VtkAlgorithmOutputData.hpp"
#include "vtk_source/file_path/FilePathData.hpp"
#include "vtk_source/vtkAlgorithmOutputData.hpp"

vtkVolume16ReaderDelegate::vtkVolume16ReaderDelegate()
    : GenericSourceReader(class_id)
    , _reader({})
{
}

vtkVolume16ReaderDelegate::~vtkVolume16ReaderDelegate() {}

QJsonObject vtkVolume16ReaderDelegate::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();

    modelJson["fp_prefix"] = _reader->GetFilePrefix();

    return modelJson;
}

void vtkVolume16ReaderDelegate::load(QJsonObject const& p)
{
    QJsonValue v = p["fp_prefix"];

    if (!v.isUndefined()) {
        QString str = v.toString();
        _reader->SetFilePrefix(str.toStdString().c_str());
    }
}

NodeDataType vtkVolume16ReaderDelegate::dataType(PortType const t,
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

std::shared_ptr<NodeData> vtkVolume16ReaderDelegate::outData(PortIndex idx)
{
    Q_UNUSED(idx)
    _reader->Update();
    return std::make_shared<VtkAlgorithmOutputData>(_reader->GetOutputPort());
}

void vtkVolume16ReaderDelegate::setInData(std::shared_ptr<NodeData> data,
                                          PortIndex const portIndex)
{
    Q_UNUSED(portIndex)

    if (auto fp = std::dynamic_pointer_cast<FilePathData>(data)) {
        _reader->SetFilePrefix(fp->filePath().toStdString().data());
        _reader->SetImageRange(1, 1);
        Q_EMIT dataUpdated(0);

    } else {
        Q_EMIT dataInvalidated(0);
    }
}
