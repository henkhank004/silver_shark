#pragma once

#include <QGraphicsItem>
#include <qpainter.h>
#include <QLineEdit>
#include <QGraphicsProxyWidget>

#include "../graph_view.hpp"
#include "../float_input_widget.hpp"
#include "engine/data.hpp"

namespace silver::ui::graph {

    class PortItem;
    struct Node;

    class MachineNodeItem : public QGraphicsItem {
    public:
        MachineNodeItem(const engine::data::GameData* game_data, const Recipe* recipe, QGraphicsItem* parent = nullptr);
        ~MachineNodeItem();

        QRectF boundingRect() const override;
        void paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

        static constexpr qreal WIDTH  = 4 * GraphView::GRID_SIZE;
        static constexpr qreal HEIGHT = 4 * GraphView::GRID_SIZE;

        template<typename F>
        void subscribe_to_input_widget(F&& callback) { input_widget_->subscribe(std::forward<F>(callback)); }

    private:
        const engine::data::GameData* game_data_;
        const Recipe* recipe_;

        std::uint32_t input_count_;
        std::uint32_t output_count_;

        QGraphicsProxyWidget* proxy_widget_;
        FloatInputWidget* input_widget_;
        std::vector<PortItem*> input_ports_;
        std::vector<PortItem*> output_ports_;

        void create_ports();
    };

}
