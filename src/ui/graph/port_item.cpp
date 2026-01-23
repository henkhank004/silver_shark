#include "port_item.hpp"

#include <qcursor.h>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>

silver::ui::graph::PortItem::PortItem(PortDirection direction, std::uint32_t index, std::uint32_t sister_ports_count_, MachineNodeItem* parent)
    : QGraphicsItem(parent), direction_(direction), index_(index), sister_ports_count_(sister_ports_count_) {
// DEBUG
    setAcceptHoverEvents(true);
    setCursor(QCursor(Qt::CrossCursor));
// END DEBUG
}

QRectF silver::ui::graph::PortItem::boundingRect() const {
    return QRectF(0, 0, width_, owning_machine_node_->height / sister_ports_count_);
}

void silver::ui::graph::PortItem::paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*) {
    QColor color;

// DEBUG
    if (direction_ == PortDirection::Input) {
        color = Qt::blue;
    } else {
        color = (index_ == 0) ? Qt::green : Qt::red;
    }
// END DEBUG

    p->setPen(Qt::black);

    p->setBrush(color);
    p->drawRect(boundingRect());

    p->drawText(QRectF(0, 0, width_ * 0.8, owning_machine_node_->height / sister_ports_count_ * 0.8),
                Qt::AlignCenter,
                "P");
}

void silver::ui::graph::PortItem::hoverEnterEvent(QGraphicsSceneHoverEvent*) {
    hovered_ = true;
    update();
}

void silver::ui::graph::PortItem::hoverLeaveEvent(QGraphicsSceneHoverEvent*) {
    hovered_ = false;
    update();
}
