#include "port_item.hpp"

#include <qcursor.h>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>

silver::ui::graph::PortItem::~PortItem() {
    count_label_->~QLabel();
}

silver::ui::graph::PortItem::PortItem(const engine::data::GameData* game_data, PortDirection direction, const Recipe* recipe, std::uint32_t index, std::uint32_t sister_ports_count_, MachineNodeItem* parent)
    : game_data_(game_data), QGraphicsItem(parent), direction_(direction), recipe_(recipe), index_(index), sister_ports_count_(sister_ports_count_), count_label_(new QLabel()), proxy_widget_(new QGraphicsProxyWidget(this)) {

#ifndef NDEBUG
    setAcceptHoverEvents(true);
    setCursor(QCursor(Qt::CrossCursor));
#endif

    std::expected<const Item*, err::Error> item_res;
    if (direction_ == PortDirection::Input)
        item_res = game_data_->items.get_obj(recipe_->ingredients[index_].first);
    else
        item_res = game_data_->items.get_obj(recipe_->products[index_].first);

#ifndef NDEBUG
    if (!item_res) {
        qDebug() << "Fialed to load item from recipe while constructing \"port_item\"";
        debug_text_ = "ERROR";
    } else {
        debug_text_ = QString::number(item_res.value()->id);
    }
#endif

    conversion_factor_ = recipe->ingredients[index_].second / recipe->products[0].second;

    parent->subscribe_to_input_widget([this](float v){update_label(v);});
    count_label_->setText("-");
    count_label_->setAttribute(Qt::WA_TransparentForMouseEvents);
    count_label_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    count_label_->setStyleSheet(
        "font-size: 12px;"
        "font-weight: italic;"
        "background: transparent;"
        "text-align: right;"
    );

    proxy_widget_->setWidget(count_label_);
    proxy_widget_->setFocusPolicy(Qt::StrongFocus);
    count_label_->setAttribute(Qt::WA_TransparentForMouseEvents);
}

QRectF silver::ui::graph::PortItem::boundingRect() const {
    return QRectF(0, 0, WIDTH, MachineNodeItem::HEIGHT / sister_ports_count_);
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

#ifndef NDEBUG
    p->drawText(QRectF(0, 0, WIDTH * 0.8, MachineNodeItem::HEIGHT / sister_ports_count_ * 0.8), Qt::AlignCenter, debug_text_);
#else
    p->drawText(QRectF(0, 0, WIDTH * 0.8, MachineNodeItem::HEIGHT / sister_ports_count_ * 0.8), Qt::AlignCenter, "");
#endif

    if (direction_ == PortDirection::Input)
        proxy_widget_->setGeometry(QRectF(-(5 + count_label_->sizeHint().width()), 0, WIDTH, GraphView::GRID_SIZE));
    if (direction_ == PortDirection::Output)
        proxy_widget_->setGeometry(QRectF(GraphView::GRID_SIZE + 5, 0, WIDTH, GraphView::GRID_SIZE));
}

void silver::ui::graph::PortItem::update_label(float value) {
    count_label_->setText(QString::number(value * conversion_factor_));
}

void silver::ui::graph::PortItem::hoverEnterEvent(QGraphicsSceneHoverEvent*) {
    hovered_ = true;
    update();
}

void silver::ui::graph::PortItem::hoverLeaveEvent(QGraphicsSceneHoverEvent*) {
    hovered_ = false;
    update();
}
