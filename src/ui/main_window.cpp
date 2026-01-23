#include "main_window.hpp"


silver::ui::MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), view_(new GraphView(this)), scene_(new QGraphicsScene(this)), settings_button_(new QPushButton(this)) {
    scene_->setSceneRect(-2000, -2000, 4000, 4000);
    scene_->setBackgroundBrush(QColor(40, 40, 40));

    view_->setScene(scene_);
    setCentralWidget(view_);

    resize(1200, 800);

//TODO: fix the styling of the settings button
    settings_button_->setFixedSize(32, 32);
    settings_button_->move(10, 10);
    settings_button_->setText("⚙");
    settings_button_->setStyleSheet("font-size: 20px;");

    connect(settings_button_, &QPushButton::clicked, this, []() {
        qDebug() << "Settings button pressed";
    });

#ifndef NDEBUG
    debug_label_ = new QLabel("DEBUG MODE", this);
    debug_label_->move(52, 10);
    debug_label_->setAttribute(Qt::WA_TransparentForMouseEvents);
    debug_label_->setFixedSize(160, 16);
    debug_label_->setStyleSheet(
        "color: red;"
        "font-size: 16px;"
        "font-weight: bold;"
    );
#endif

    // TEMP: add one template node
    auto* node = new graph::MachineNodeItem();
    node->setPos(100, 100);
    scene_->addItem(node);

    view_->lower();
}


void silver::ui::MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);

    view_->setGeometry(centralWidget()->rect());
}