#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->qMyExtLabel, SIGNAL(MouseLeave()), this, SLOT(OnMouseLeave()));
    connect(ui->qMyExtLabel, SIGNAL(MouseEnter()), this, SLOT(OnMouseEnter()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::OnMouseLeave()
{
    qDebug() << "OnMouseLeave";
}

void Widget::OnMouseEnter()
{
    qDebug() << "OnMouseEnter";
}
