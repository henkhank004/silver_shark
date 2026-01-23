#pragma once

#include <QGraphicsView>
#include <QWheelEvent>
#include <QPoint>
#include <QTimer>

namespace silver::ui {

    class GraphView : public QGraphicsView {
        Q_OBJECT
    public:
        static constexpr std::uint32_t GRID_SIZE = 30;

        explicit GraphView(QWidget* parent = nullptr);

    protected:
        void wheelEvent(QWheelEvent* event) override;
        void mousePressEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        void mouseReleaseEvent(QMouseEvent* event) override;
        void drawBackground(QPainter* painter, const QRectF& rect) override;

    private:
        bool panning_ = false;
        QPoint last_mouse_pos_;

        double zoom_ = 1.0;
        double target_zoom_ = 1.0;

        QTimer zoom_timer_;

        static constexpr double zoom_step_ = 1.15;
        static constexpr double min_zoom_  = 0.25;
        static constexpr double max_zoom_  = 4.0;
    };

}
