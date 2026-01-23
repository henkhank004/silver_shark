#pragma once

#include <QGraphicsItem>

#include "machine_node_item.hpp"
#include "port_direction.hpp"

namespace silver::ui::graph {

    class PortItem : public QGraphicsItem {
    public:
        PortItem(PortDirection direction, std::uint32_t index, std::uint32_t sister_ports_count, MachineNodeItem* parent = nullptr);

        QRectF boundingRect() const override;
        void paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    protected:
        void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
        void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    private:
        MachineNodeItem* owning_machine_node_;
        PortDirection direction_;
        std::uint32_t index_;
        std::uint32_t sister_ports_count_;

        bool hovered_ = false;

        static constexpr qreal width_ = 60.0;
    };

}

