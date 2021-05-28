#include "model_view.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    model_view w;
//    w.show();
    StandardItemModelWidget widget;
    widget.show();

    return a.exec();
}
