#pragma once

#include <QMainWindow>
#include "graph/machine_node_item.hpp"

class QGraphicsView;
class QGraphicsScene;

namespace silver::ui {

    class MainWindow : public QMainWindow {
        Q_OBJECT
    public:
        explicit MainWindow(QWidget* parent = nullptr);

    private:
        QGraphicsView*  view_;
        QGraphicsScene* scene_;
    };

}
