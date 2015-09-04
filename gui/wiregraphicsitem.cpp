#include "wiregraphicsitem.h"

#include "flowchart/flowchart.h"
#include "flowchart/block.h"
#include <QRectF>
#include <QSizeF>
#include <QPainterPath>
#include <QPointF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

QPointF WireGraphicsItem::blockInputPinPos(const BlockPin bp) const {
    Block block = m_flow->blocks[bp.first];
    QPointF blockPos = QPointF(block.xPos, block.yPos);
    BlockType blockType = block.blockType;
    QPointF relativePinPos = blockType.inputPinCenterPos(QString::fromStdString(bp.second));
    QPointF pinPos = blockPos + relativePinPos;
    return pinPos;
}

QPointF WireGraphicsItem::blockOutputPinPos(const BlockPin bp) const {
    Block block = m_flow->blocks[bp.first];
    QPointF blockPos = QPointF(block.xPos, block.yPos);
    BlockType blockType = block.blockType;
    QPointF relativePinPos = blockType.outputPinCenterPos(QString::fromStdString(bp.second));
    QPointF pinPos = blockPos + relativePinPos;
    return pinPos;
}

WireGraphicsItem::WireGraphicsItem(FlowChart *flow, BlockPin blockPin) {
    m_flow = flow;
    m_blockPin = blockPin;
}

QRectF WireGraphicsItem::boundingRect() const {
    QPointF myPinPos = blockOutputPinPos(m_blockPin);
    QRectF bounds(myPinPos, QSizeF(0,0));
    auto otherBlockPins = m_flow->blocks[m_blockPin.first].outputConnections[m_blockPin.second];
    for (BlockPin otherBlockPin : otherBlockPins) {
        QPointF otherPinPos = blockInputPinPos(otherBlockPin);
        if (otherPinPos.x() < bounds.left()) {
            bounds.setLeft(otherPinPos.x());
        } else if (otherPinPos.x() > bounds.right()) {
            bounds.setRight(otherPinPos.x());
        }
        if (otherPinPos.y() < bounds.top()) {
            bounds.setTop(otherPinPos.y());
        } else if (otherPinPos.y() > bounds.bottom()) {
            bounds.setBottom(otherPinPos.y());
        }
    }
    return bounds;
}

QPainterPath WireGraphicsItem::shape() const {
    return QPainterPath();
}

void WireGraphicsItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
    painter->setPen(QPen(QColor(0,0,0), 15));
    QPointF myPinPos = blockOutputPinPos(m_blockPin);
    auto otherBlockPins = m_flow->blocks[m_blockPin.first].outputConnections[m_blockPin.second];
    for (BlockPin otherBlockPin : otherBlockPins) {
        QPointF otherPinPos = blockInputPinPos(otherBlockPin);
        painter->drawLine(myPinPos, otherPinPos);
    }
}

