#include "graph_view.hpp"

#include <QMouseEvent>
#include <QScrollBar>


silver::ui::GraphView::GraphView(QWidget* parent) : QGraphicsView(parent) {
    setRenderHint(QPainter::Antialiasing);
    setDragMode(NoDrag);

    setViewportUpdateMode(FullViewportUpdate);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    zoom_timer_.setInterval(16);
    connect(&zoom_timer_, &QTimer::timeout, this, [this]() {
        const double diff = target_zoom_ - zoom_;
        if (std::abs(diff) < 0.001) {
            zoom_ = target_zoom_;
            zoom_timer_.stop();
            return;
        }

        const double step = diff * 0.25;
        const double factor = (zoom_ + step) / zoom_;
        zoom_ += step;

        scale(factor, factor);
    });

}


void silver::ui::GraphView::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::MiddleButton) {
        panning_ = true;
        last_mouse_pos_ = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }
    QGraphicsView::mousePressEvent(event);
}


void silver::ui::GraphView::mouseMoveEvent(QMouseEvent* event) {
    if (panning_) {
        QPoint delta = event->pos() - last_mouse_pos_;
        last_mouse_pos_ = event->pos();

        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());

        event->accept();
        return;
    }
    QGraphicsView::mouseMoveEvent(event);
}


void silver::ui::GraphView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::MiddleButton) {
        panning_ = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }
    QGraphicsView::mouseReleaseEvent(event);
}


void silver::ui::GraphView::wheelEvent(QWheelEvent* event) {
    if (event->angleDelta().y() == 0) {
        event->ignore();
        return;
    }

    const double factor =
        event->angleDelta().y() > 0 ? zoom_step_ : (1.0 / zoom_step_);

    target_zoom_ *= factor;
    target_zoom_ = std::clamp(target_zoom_, min_zoom_, max_zoom_);

    if (!zoom_timer_.isActive()) {
        zoom_timer_.start();
    }

    event->accept();
}


void silver::ui::GraphView::drawBackground(QPainter* painter, const QRectF& rect) {
    painter->fillRect(rect, QColor(30, 30, 30));

    QPen minor_pen(QColor(45, 45, 45));
    QPen major_pen(QColor(60, 60, 60));

    minor_pen.setWidth(1);
    major_pen.setWidth(2);

    const int left   = static_cast<int>(std::floor(rect.left())) - (static_cast<int>(rect.left()) % GRID_SIZE);
    const int right  = static_cast<int>(std::ceil(rect.right()));
    const int top    = static_cast<int>(std::floor(rect.top())) - (static_cast<int>(rect.top()) % GRID_SIZE);
    const int bottom = static_cast<int>(std::ceil(rect.bottom()));

    for (int x = left; x <= right; x += GRID_SIZE) {
        painter->setPen((x % (GRID_SIZE * 4) == 0) ? major_pen : minor_pen);
        painter->drawLine(x, top, x, bottom);
    }

    for (int y = top; y <= bottom; y += GRID_SIZE) {
        painter->setPen((y % (GRID_SIZE * 4) == 0) ? major_pen : minor_pen);
        painter->drawLine(left, y, right, y);
    }
}