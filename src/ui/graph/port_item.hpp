#pragma once

#include <QGraphicsItem>

#include "machine_node_item.hpp"
#include "port_direction.hpp"

namespace silver::ui::graph {

    class PortItem : public QGraphicsItem {
    public:
        static constexpr qreal WIDTH = GraphView::GRID_SIZE;

        PortItem(const engine::data::GameData* game_data, PortDirection direction, const Recipe* recipe, std::uint32_t index, std::uint32_t sister_ports_count, MachineNodeItem* parent = nullptr);

        QRectF boundingRect() const override;
        void paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    protected:
        void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
        void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    private:
        const engine::data::GameData* game_data_;
        const Recipe* recipe_;
        MachineNodeItem* owning_machine_node_;
        PortDirection direction_;
        std::uint32_t index_;
        std::uint32_t sister_ports_count_;

        bool hovered_ = false;
    };

}

