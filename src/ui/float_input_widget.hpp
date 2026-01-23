#pragma once

#include <QLineEdit>
#include <qwidget.h>
#include <QTimer>

namespace silver::ui::graph {

    class FloatInputWidget : public QWidget {
        Q_OBJECT

    public:
        FloatInputWidget(int width = 0, int height = 0, QWidget* parent = nullptr);
        float value;

    private:
        QLineEdit* line_edit_;
        QTimer* update_timer_;
    };

}
