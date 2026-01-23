#include <iostream>
#include <QApplication>
#include <QMessageBox>
#include "engine/data.hpp"
#include "ui/main_window.hpp"

#define DATAFILE "/home/daan/silver_shark/src/data/data.json"

int main(int argc, char** argv) {
        QApplication app(argc, argv);

#ifndef NDEBUG
    std::cout << "Running in debug mode." << std::endl;
#endif

        auto game_data_res =
            silver::engine::data::load_game_data(DATAFILE);

        if (!game_data_res) {
            QMessageBox::critical(
                nullptr,
                "Failed to load data",
                QString::fromStdString(game_data_res.error().msg)
            );
            return game_data_res.error().code;
        }

        silver::engine::data::GameData game_data =
            std::move(*game_data_res);

        silver::ui::MainWindow window;
        window.show();

        return app.exec();
}