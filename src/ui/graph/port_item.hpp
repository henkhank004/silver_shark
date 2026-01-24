#pragma once

#include <QGraphicsItem>
#include <QLabel>

#include "machine_node_item.hpp"
#include "port_direction.hpp"

namespace silver::ui::graph {

    class PortItem : public QGraphicsItem {
    public:
        ~PortItem();

        static constexpr qreal WIDTH = GraphView::GRID_SIZE;

        PortItem(const engine::data::GameData* game_data, PortDirection direction, const Recipe* recipe, std::uint32_t index, std::uint32_t sister_ports_count, MachineNodeItem* parent = nullptr);

        QRectF boundingRect() const override;
        void paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

        void update_label(float value);

    protected:
        void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
        void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    private:
        QLabel* count_label_;
        QGraphicsProxyWidget* proxy_widget_;
        const engine::data::GameData* game_data_;
        const Recipe* recipe_;
        PortDirection direction_;
        std::uint32_t index_;
        std::uint32_t sister_ports_count_;
        bool hovered_ = false;
        float conversion_factor_;

#ifndef NDEBUG
        QString debug_text_;
#endif
    };

}

