#ifndef DB2B934B_C242_4928_B6C2_25FCC079AB28
#define DB2B934B_C242_4928_B6C2_25FCC079AB28

#include <utility>

#include <QtNodes/NodeData>

#include "vtk_shapes/vtk_shape.hpp"

using QtNodes::NodeData;
using QtNodes::NodeDataType;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class DecimalData : public NodeData

{
  public:
    DecimalData()
        : DecimalData(0.0)
    {
    }
    DecimalData(QString name)
        : _number(0.0)
        , _name(std::move(name))
    {
    }

    DecimalData(double const number)
        : _number(number)
    {
    }

    NodeDataType type() const override
    {
        return NodeDataType {"decimal", _name};
    }

    double number() const { return _number; }

    QString numberAsText() const { return QString::number(_number, 'f'); }

  private:
    double _number;
    QString _name = "decimal";
};

#endif /* DB2B934B_C242_4928_B6C2_25FCC079AB28 */
