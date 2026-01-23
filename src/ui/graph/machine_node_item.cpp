#include "machine_node_item.hpp"
#include "port_item.hpp"
#include "port_direction.hpp"

#include <QPainter>

silver::ui::graph::MachineNodeItem::MachineNodeItem() {
    setFlags(
        ItemIsMovable |
        ItemIsSelectable
    );

    create_ports();
}

QRectF silver::ui::graph::MachineNodeItem::boundingRect() const {
    return QRectF(0, 0, width, height);
}

void silver::ui::graph::MachineNodeItem::paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*) {
    p->setPen(Qt::black);
    p->setBrush(QColor(230, 230, 230));
    p->drawRect(boundingRect());

    p->setPen(Qt::black);
    p->drawText(QRectF(0, 0, width, 24),
                Qt::AlignCenter,
                "Machine");
}

void silver::ui::graph::MachineNodeItem::create_ports() {
    constexpr qreal start_y = 0;
    const qreal spacing_in = height / input_count_;
    const qreal spacing_out = height / output_count_;

    for (int i = 0; i < input_count_; ++i) {
        auto* port = new PortItem(PortDirection::Input, i, input_count_, this);
        port->setPos(0, start_y + i * spacing_in);
        input_ports_.push_back(port);
    }

    for (int i = 0; i < output_count_; ++i) {
        auto* port = new PortItem(PortDirection::Output, i, output_count_, this);
        port->setPos(width, start_y + i * spacing_out);
        output_ports_.push_back(port);
    }
}
