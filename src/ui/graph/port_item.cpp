#include "port_item.hpp"

#include <qcursor.h>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>

silver::ui::graph::PortItem::PortItem(const engine::data::GameData* game_data, PortDirection direction, const Recipe* recipe, std::uint32_t index, std::uint32_t sister_ports_count_, MachineNodeItem* parent)
    : game_data_(game_data), QGraphicsItem(parent), direction_(direction), recipe_(recipe), index_(index), sister_ports_count_(sister_ports_count_) {

#ifndef NDEBUG
    setAcceptHoverEvents(true);
    setCursor(QCursor(Qt::CrossCursor));
#endif
}

QRectF silver::ui::graph::PortItem::boundingRect() const {
    return QRectF(0, 0, WIDTH, owning_machine_node_->HEIGHT / sister_ports_count_);
}

void silver::ui::graph::PortItem::paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*) {
    QColor color = Qt::gray;

#ifndef NDEBUG
    if (direction_ == PortDirection::Input) {
        color = Qt::blue;
    } else {
        color = (index_ == 0) ? Qt::green : Qt::red;
    }
#endif

    p->setPen(Qt::black);

    p->setBrush(color);
    p->drawRect(boundingRect());

    QString text = "P";
    std::expected<const Item*, err::Error> item_res;
    if (direction_ == PortDirection::Input)
        item_res = game_data_->items.get_obj(recipe_->ingredients[index_].first);
    else
        item_res = game_data_->items.get_obj(recipe_->products[index_].first);

    /* TEMP */
    if (!item_res) {
        qDebug() << "Fialed to load item from recipe while constructing \"port_item\"";
        text = "ERROR";
    } else {
        text = QString::number(item_res.value()->id);
    }
    /* TEMP */

    p->drawText(QRectF(0, 0, WIDTH * 0.8, MachineNodeItem::HEIGHT / sister_ports_count_ * 0.8), Qt::AlignCenter, text);
}

void silver::ui::graph::PortItem::hoverEnterEvent(QGraphicsSceneHoverEvent*) {
    hovered_ = true;
    update();
}

void silver::ui::graph::PortItem::hoverLeaveEvent(QGraphicsSceneHoverEvent*) {
    hovered_ = false;
    update();
}
