#ifndef AF3B6AE5_9561_478D_874D_018EE93FE036
#define AF3B6AE5_9561_478D_874D_018EE93FE036

#include <utility>

#include <QtNodes/NodeData>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class TextData : public NodeData
{
  public:
    TextData() = default;

    TextData(QString text)
        : _text(std::move(text))
    {
    }

    [[nodiscard]] NodeDataType type() const override
    {
        return NodeDataType {"text", "Text"};
    }

    [[nodiscard]] QString text() const { return _text; }

  private:
    QString _text;
};

#endif /* AF3B6AE5_9561_478D_874D_018EE93FE036 */
