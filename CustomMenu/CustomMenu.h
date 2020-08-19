#pragma once

#include <QtGui/QMouseEvent>
#include <QtWidgets/Qmenu>
#include <QtWidgets/QMainWindow>
#include "ui_CustomMenu.h"

class CustomMenu : public QMainWindow
{
    Q_OBJECT

public:
    CustomMenu(QWidget *parent = Q_NULLPTR);

protected:
    void mouseReleaseEvent(QMouseEvent *mouseevent);

private:
    void initMenu();

private:
    Ui::CustomMenuClass ui;
    QMenu   *m_AppMenu;
};
