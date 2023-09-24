#ifndef FILEPATHDATA_HPP
#define FILEPATHDATA_HPP

#include <utility>

#include <QtNodes/NodeData>
using QtNodes::NodeData;
using QtNodes::NodeDataType;
class FilePathData : public NodeData
{
  public:
    FilePathData() = default;

    FilePathData(QString fp)
        : _file_path(std::move(fp))
    {
    }
    [[nodiscard]] NodeDataType type() const override
    {
        return NodeDataType {"filePath", "filePath"};
    }

    [[nodiscard]] QString filePath() const { return _file_path; }

  private:
    QString _file_path;
};

#endif