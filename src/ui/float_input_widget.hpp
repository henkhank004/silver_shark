#pragma once

#include <QLineEdit>
#include <qwidget.h>
#include <QTimer>

namespace silver::ui::graph {

    class FloatInputWidget : public QWidget {
        Q_OBJECT

    public:
        FloatInputWidget(int width = 0, int height = 0, QWidget* parent = nullptr);
        template <typename F>
        void subscribe(F&& callback) {
            subscribers.emplace_back(std::forward<F>(callback));
        }

    private:
        std::vector<std::function<void(float)>> subscribers;
        QLineEdit* line_edit_;
        QTimer* update_timer_;
    };

}
