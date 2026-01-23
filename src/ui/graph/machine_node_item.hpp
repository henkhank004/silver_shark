#pragma once

#include <QGraphicsItem>
#include <qpainter.h>
#include "../graph_view.hpp"

namespace silver::ui::graph {

    class PortItem;
    struct Node;

    class MachineNodeItem : public QGraphicsItem {
    public:
        MachineNodeItem();

        QRectF boundingRect() const override;
        void paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

        static constexpr qreal WIDTH  = 6 * GraphView::GRID_SIZE;
        static constexpr qreal HEIGHT = 4 * GraphView::GRID_SIZE;

    private:
        int input_count_  = 2;
        int output_count_ = 2;

        std::vector<PortItem*> input_ports_;
        std::vector<PortItem*> output_ports_;

        void create_ports();
    };

}
