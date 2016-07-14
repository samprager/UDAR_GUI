#include "udar_controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UDAR_Controller w;
    w.show();

    return a.exec();
}
