#include "main_window.hpp"

#include <QGraphicsView>
#include <QGraphicsScene>

silver::ui::MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), view_(new QGraphicsView(this)), scene_(new QGraphicsScene(this)) {
    scene_->setBackgroundBrush(QColor(180, 180, 180));
    view_->setScene(scene_);
    setCentralWidget(view_);

    resize(1200, 800);

    // TEMP: add one template node
    auto* node = new graph::MachineNodeItem();
    node->setPos(100, 100);
    scene_->addItem(node);
}
