#include "mainwindow.h"
#include "GifButton.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	GifButton *gif_button = new GifButton(this, ":/MainWindow/res/image/register_btn_loading.gif");
	gif_button->setFont(QFont("Microsoft YaHei"));
	gif_button->setGeometry((this->rect().width()-200)/2, 50, 200, 32);
	gif_button->SetTextColor(Qt::white);
	gif_button->SetText(tr("Registering"));
	// gif_button->Start();
}
