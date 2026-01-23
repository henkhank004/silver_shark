#pragma once

#include <QGraphicsItem>
#include <qpainter.h>

namespace silver::ui::graph {

    class PortItem;
    struct Node;

    class MachineNodeItem : public QGraphicsItem {
    public:
        MachineNodeItem();

        QRectF boundingRect() const override;
        void paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

        static constexpr qreal width  = 180.0;
        static constexpr qreal height = 120.0;

    private:
        int input_count_  = 2;
        int output_count_ = 2;

        std::vector<PortItem*> input_ports_;
        std::vector<PortItem*> output_ports_;

        void create_ports();
    };

}
