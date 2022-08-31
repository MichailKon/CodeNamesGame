#include <QApplication>
#include "GameWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto window = new GameWindow();
    window->show();
    return QApplication::exec();
}
