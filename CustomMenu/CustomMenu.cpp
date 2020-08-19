#include "CustomMenu.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidgetAction>

#include <Windows.h>

QString button = "QPushButton {     "           
        "font: 12px \"Microsoft YaHei UI\";"
        "color: #444444;"
        "background-color:#FFFFFF;"
        "text-align:left;"
        "padding-left:34px;"
        "width:116px;"
        "height:32px;"
        "border-image: %1 0 0 0 0 repeat  repeat;"
        "border-width: 0px; "
        "border-radius: 0px;"
        "}"

        "QPushButton:hover { "
        "background-color:#3372E4;"
        "color: #FFFFFF;"
        "border-image: %1 0 0 0 116 repeat  repeat;"
        "border-width: 0px; "
        "border-radius: 0px;"
        "}";

CustomMenu::CustomMenu(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    initMenu();

      	//设置窗口置顶
	::SetWindowPos((HWND)this->winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	::SetWindowPos((HWND)this->winId(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
}

void CustomMenu::mouseReleaseEvent(QMouseEvent *mouseevent)
{
    if (mouseevent->button() == Qt::RightButton) {
        m_AppMenu->exec(QCursor::pos());
	}
}

void CustomMenu::initMenu()
{
    m_AppMenu = new QMenu(this);
    m_AppMenu->setStyleSheet(
    "QMenu {"
    "background-color:#FFFFFF;"
    "border: 2px solid #FFFFFF;"
    "width:120px;"
    "height:137px;"
    "}"

    "QMenu::separator {"
    "height: 1px; "
    "background: #D9DADB;"
    "}"
        );

    	// 开始游戏
    QPushButton *btn = new QPushButton(tr("start game"), m_AppMenu);
    btn->setMaximumWidth(116);
    btn->setStyleSheet(button.arg("url(:/CustomMenu/res/menu_startup.png)"));
    QWidgetAction *widgetaction = new QWidgetAction(m_AppMenu);
    widgetaction->setDefaultWidget(btn);
    m_AppMenu->addAction(widgetaction);

    // 置顶
     btn = new QPushButton(tr("set top"), m_AppMenu);
     btn->setMaximumWidth(116);
     btn->setStyleSheet(button.arg("url(:/CustomMenu/res/menu_top.png)"));
     widgetaction = new QWidgetAction(m_AppMenu);
     widgetaction->setDefaultWidget(btn);
     m_AppMenu->addAction(widgetaction);

	// 创建快捷方式
    btn = new QPushButton(tr("create shortcut"), m_AppMenu);
    btn->setMaximumWidth(116);
    btn->setStyleSheet(button.arg("url(:/CustomMenu/res/menu_shortcut.png)"));
    widgetaction = new QWidgetAction(m_AppMenu);
    widgetaction->setDefaultWidget(btn);
    m_AppMenu->addAction(widgetaction);

	//加2px间距
	QLabel *firstLine = new QLabel();
    firstLine->setFixedSize(QSize(118, 2));
	widgetaction = new QWidgetAction(m_AppMenu);
	widgetaction->setDefaultWidget(firstLine);
	m_AppMenu->addAction(widgetaction);

    m_AppMenu->addSeparator();

	firstLine = new QLabel();
    firstLine->setFixedSize(QSize(118, 2));
	widgetaction = new QWidgetAction(m_AppMenu);
	widgetaction->setDefaultWidget(firstLine);
	m_AppMenu->addAction(widgetaction);

    // 删除游戏
    btn = new QPushButton(tr("delete game"), m_AppMenu);
    btn->setMaximumWidth(116);
    btn->setStyleSheet(button.arg(""));
    widgetaction = new QWidgetAction(m_AppMenu);
    widgetaction->setDefaultWidget(btn);
    m_AppMenu->addAction(widgetaction);
}
