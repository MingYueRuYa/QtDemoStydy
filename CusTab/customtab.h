#pragma once

#include "ui_CustomTab.h"
#include "tabbutton.h"

#include <QtWidgets/QMainWindow>
#include <QtGui/QMouseEvent>

#include <list>

using std::list;

//实现无边框拉伸
enum Direction {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	LEFTTOP,
	LEFTBOTTOM,
	RIGHTBOTTOM,
	RIGHTTOP,
	NONE
};
#define PADDING 1

class CustomTab : public QMainWindow
{
	Q_OBJECT

public:
	CustomTab(QWidget *parent = Q_NULLPTR);
	~CustomTab();
	void region(const QPoint &point);

protected:
	bool nativeEvent(const QByteArray &eventType, void *message, long *result);
	void mousePressEvent(QMouseEvent *e);
	void mouseDoubleClickEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void resizeEvent(QResizeEvent *event);
	bool eventFilter(QObject *object, QEvent *event);

protected slots:
	void OnClose();
	void OnMin();
	void OnMax();
    void OnRestor();
    void OnTabBtnPush(TabButton *tabButton);
    void OnTabClose(TabButton *tabButton);

private:
	void initUI();
	void connectSignals();
    void resizeTabBtn();
    void setStyle();
    TabButton* createTabButton();

private:
	Ui::CustomTabClass ui;
	bool m_bMouseLeftPress;
	bool m_bInSize = false;
    list<TabButton*> mListTabBtn;

	QPoint m_DragPosition;
    bool m_isLeftPressDown;
	Direction m_dir;
};

