#include "CustomMenu.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CustomMenu w;
    w.show();
    return a.exec();
}
