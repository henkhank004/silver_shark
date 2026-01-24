#include "float_input_widget.hpp"

#include <QDoubleValidator>

silver::ui::graph::FloatInputWidget::FloatInputWidget(const int width, const int height, QWidget*) : line_edit_(new QLineEdit(this)) {
    float base_value = 1.0f;

    line_edit_ = new QLineEdit(this);
    QDoubleValidator* validator = new QDoubleValidator(1e38, 1e38, 4, this);
    line_edit_->setValidator(validator);
    line_edit_->setAlignment(Qt::AlignCenter);
    line_edit_->setPlaceholderText(QString::number(base_value));
    if (width != 0)
        line_edit_->setFixedWidth(width);
    if (height != 0)
        line_edit_->setFixedHeight(height);

    update_timer_ = new QTimer(this);
    update_timer_->setInterval(500);
    update_timer_->setSingleShot(true);

    connect(line_edit_, &QLineEdit::textChanged, [this]() {
        update_timer_->start();
    });

    connect(update_timer_, &QTimer::timeout, this, [&]() {
        const auto value = static_cast<float>(line_edit_->text().toDouble());
        for (auto s : subscribers)
            s(value);
    });
}