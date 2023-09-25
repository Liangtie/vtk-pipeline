#ifndef SLICEDATA_HPP
#define SLICEDATA_HPP
#include <utility>

#include <QtNodes/NodeData>
using QtNodes::NodeData;
using QtNodes::NodeDataType;
struct SliceData : public NodeData
{
    [[nodiscard]] NodeDataType type() const override
    {
        return NodeDataType {"slices", "slices"};
    }

    [[nodiscard]] auto getPrefix() const { return _dir + "/" + _prefix; }
    QString _dir;
    QString _prefix;
    int _start_idx {};
    int _end_idx {};
};

#endif