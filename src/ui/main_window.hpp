#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "graph/machine_node_item.hpp"
#include "graph_view.hpp"


namespace silver::ui {

    class MainWindow : public QMainWindow {
        Q_OBJECT
    public:
        explicit MainWindow(QWidget* parent = nullptr);

    protected:
        void resizeEvent(QResizeEvent* event) override;

    private:
        GraphView*  view_;
        QGraphicsScene* scene_;
        QPushButton* settings_button_;
#ifndef NDEBUG
        QLabel* debug_label_;
#endif
    };

}
