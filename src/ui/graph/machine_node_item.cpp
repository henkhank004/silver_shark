#include "machine_node_item.hpp"
#include "port_item.hpp"
#include "port_direction.hpp"

#include <QPainter>

silver::ui::graph::MachineNodeItem::MachineNodeItem(const engine::data::GameData* game_data, const Recipe* recipe, QGraphicsItem*)
    : game_data_(game_data), recipe_(recipe), proxy_widget_(new QGraphicsProxyWidget(this)) {
    input_widget_ = new FloatInputWidget(WIDTH, GraphView::GRID_SIZE);

    setFlags(
        ItemIsMovable |
        ItemIsSelectable
    );

    input_count_ = recipe_->ingredients.size();
    output_count_ = recipe_->products.size();

    create_ports();

    proxy_widget_->setWidget(input_widget_);
    proxy_widget_->setFocusPolicy(Qt::StrongFocus);
    proxy_widget_->setGeometry(QRectF(0, 3 * GraphView::GRID_SIZE, WIDTH, GraphView::GRID_SIZE));

}

silver::ui::graph::MachineNodeItem::~MachineNodeItem() {
    input_widget_->~FloatInputWidget();
}

QRectF silver::ui::graph::MachineNodeItem::boundingRect() const {
    return QRectF(0, 0, WIDTH, HEIGHT - GraphView::GRID_SIZE);
}

void silver::ui::graph::MachineNodeItem::paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*) {
    p->setPen(Qt::black);
    p->setBrush(QColor(230, 230, 230));
    p->drawRect(boundingRect());

    p->setPen(Qt::black);

    // TEMP:
    QString name = QString::number(recipe_->id);

    p->drawText(QRectF(0, 0, WIDTH, 24), Qt::AlignCenter, name);
}

void silver::ui::graph::MachineNodeItem::create_ports() {
    constexpr qreal start_y = 0;
    const qreal spacing_in = HEIGHT / input_count_;
    const qreal spacing_out = HEIGHT / output_count_;

    for (int i = 0; i < input_count_; i++) {
        auto* port = new PortItem(game_data_, PortDirection::Input, recipe_, i, input_count_, this);
        port->setPos(-PortItem::WIDTH, start_y + i * spacing_in);
        input_ports_.push_back(port);
    }

    for (int i = 0; i < output_count_; i++) {
        auto* port = new PortItem(game_data_, PortDirection::Output, recipe_, i, output_count_, this);
        port->setPos(WIDTH, start_y + i * spacing_out);
        output_ports_.push_back(port);
    }
}
