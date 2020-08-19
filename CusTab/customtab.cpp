#include "customtab.h"

#include <QtCore/QFile>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonParseError>

#include <memory>
#include <algorithm>

#include <Windows.h>

#define FCBROWSERWIDTH	1200
#define FCBROWSERHEIGHT	710

const QString k1KSTYLE = ":/1kCustomTab/style/default_100_precent/%1";
const QString k1KRESOURCE = ":/1kCustomTab/image/default_100_precent/%1";

const int kLAYOUT_ITEM_WIDTH = 48;

const int kMAX_TAB = 10;

using std::shared_ptr;

CustomTab::CustomTab(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

    m_dir               = NONE;
    m_isLeftPressDown   = false;

	this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
	initUI();
}

CustomTab::~CustomTab()
{
}

bool CustomTab::eventFilter(QObject *object, QEvent *event)
{
	return QMainWindow::eventFilter(object, event);
}

bool CustomTab::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	return QMainWindow::nativeEvent(eventType, message, result);
}

void CustomTab::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton) {
		//拉伸
		m_isLeftPressDown = true;
		if (m_dir != NONE){
			this->mouseGrabber();
		}
		else{
			m_DragPosition = e->globalPos() - this->frameGeometry().topLeft();
		}
		return;
	}

	QMainWindow::mousePressEvent(e);
}

void CustomTab::mouseDoubleClickEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton){
		if (ui.captionWidget->geometry().contains(e->pos()))
		{
			if (this->isMaximized()){
				OnRestor();
			}
			else{
				OnMax();
			}
		}
	}

	QMainWindow::mouseDoubleClickEvent(e);
}

void CustomTab::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton){
		m_isLeftPressDown = false;
		if (m_dir != NONE){
			this->releaseMouse();
			this->setCursor(QCursor(Qt::ArrowCursor));
			m_bInSize = false;
		}
	}

	return __super::mouseReleaseEvent(e);
}

void CustomTab::mouseMoveEvent(QMouseEvent *e)
{
	if (e->buttons()&Qt::LeftButton)
	{
		if (!isMaximized()){
			ui.btn_restore->setVisible(false);
			ui.btn_max->setVisible(true);
		}

		if (ui.captionWidget->geometry().contains(e->pos()) && ! m_bInSize)
		{
			if (ReleaseCapture())
			{
				SendMessage(HWND(this->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
			}
		}
	}

	//拉伸
	QPoint gloPoint = e->globalPos();
	QRect rect = this->rect();
	QPoint tl = mapToGlobal(rect.topLeft());
	QPoint rb = mapToGlobal(rect.bottomRight());

	if (!m_isLeftPressDown) {
		this->region(gloPoint);
	}
	else {

		if (m_dir != NONE) {
			QRect rMove(tl, rb);

			switch (m_dir) {
			case LEFT:
				if (rb.x() - gloPoint.x() <= this->minimumWidth())
					rMove.setX(tl.x());
				else
					rMove.setX(gloPoint.x());
				break;
			case RIGHT:
				rMove.setWidth(gloPoint.x() - tl.x());
				break;
			case UP:
				if (rb.y() - gloPoint.y() <= this->minimumHeight())
					rMove.setY(tl.y());
				else
					rMove.setY(gloPoint.y());
				break;
			case DOWN:
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			case LEFTTOP:
				if (rb.x() - gloPoint.x() <= this->minimumWidth())
					rMove.setX(tl.x());
				else
					rMove.setX(gloPoint.x());
				if (rb.y() - gloPoint.y() <= this->minimumHeight())
					rMove.setY(tl.y());
				else
					rMove.setY(gloPoint.y());
				break;
			case RIGHTTOP:
				rMove.setWidth(gloPoint.x() - tl.x());
				rMove.setY(gloPoint.y());
				break;
			case LEFTBOTTOM:
				rMove.setX(gloPoint.x());
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			case RIGHTBOTTOM:
				rMove.setWidth(gloPoint.x() - tl.x());
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			default:
				break;
			}
			this->setGeometry(rMove);
		}
	}

	QMainWindow::mouseMoveEvent(e);
}

void CustomTab::resizeEvent(QResizeEvent *event)
{
    QSize size = event->size();

    resizeTabBtn();

    QMainWindow::resizeEvent(event);
}

void CustomTab::region(const QPoint &point){
	// 获取窗体在屏幕上的位置区域，tl为topleft点，rb为rightbottom点
	QRect rect = this->rect();
	QPoint tl = mapToGlobal(rect.topLeft());
	QPoint rb = mapToGlobal(rect.bottomRight());

	int x = point.x();
	int y = point.y();

	if (tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
		// 左上角
		m_dir = LEFTTOP;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
		m_bInSize = true;
	}
	else if (x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
		// 右下角
		m_dir = RIGHTBOTTOM;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));
		m_bInSize = true;
	}
	else if (x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
		//左下角
		m_dir = LEFTBOTTOM;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
		m_bInSize = true;
	}
	else if (x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
		// 右上角
		m_dir = RIGHTTOP;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
		m_bInSize = true;
	}
	else if (x <= tl.x() + PADDING && x >= tl.x()) {
		// 左边
		m_dir = LEFT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
		m_bInSize = true;
	}
	else if (x <= rb.x() && x >= rb.x() - PADDING) {
		// 右边
		m_dir = RIGHT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
		m_bInSize = true;
	}
	else if (y >= tl.y() && y <= tl.y() + PADDING){
		// 上边
		m_dir = UP;
		this->setCursor(QCursor(Qt::SizeVerCursor));
		m_bInSize = true;
	}
	else if (y <= rb.y() && y >= rb.y() - PADDING) {
		// 下边
		m_dir = DOWN;
		this->setCursor(QCursor(Qt::SizeVerCursor));
		m_bInSize = true;
	}
	else {
		// 默认
		m_dir = NONE;
		this->setCursor(QCursor(Qt::ArrowCursor));
		m_bInSize = false;
	}
}

void CustomTab::OnClose()
{
    this->close();
}

void CustomTab::OnMin()
{
	this->showMinimized();
}

void CustomTab::OnMax()
{
	ui.btn_max->setVisible(false);
	ui.btn_restore->setVisible(true);
	this->showMaximized();
}

void CustomTab::OnRestor()
{
	ui.btn_restore->setVisible(false);
	ui.btn_max->setVisible(true);
	showNormal();
}

void CustomTab::OnTabBtnPush(TabButton *tabButton)
{
    std::for_each(mListTabBtn.begin(), mListTabBtn.end(), [tabButton] (TabButton *tabbtn) {
        if (tabbtn != tabButton) { 
            tabbtn->SetPushStats(TabButton::PushStatus::Normal); 
        }
    });

    tabButton->SetPushStats(TabButton::PushStatus::Press);

    QSize size = this->size();
    size -= QSize(0, ui.captionWidget->height());
}

void CustomTab::OnTabClose(TabButton *tabButton)
{
    tabButton->setVisible(false);
    tabButton->disconnect();
    // 因为这个消息是Button发送过来的，不要直接删除Button对象，只能置为删除的标记
    tabButton->SetDelete(true);
    ui.tab_widget->layout()->removeWidget(tabButton);

    // 滚动tab
    list<TabButton *>::iterator ifind = std::find_if(mListTabBtn.begin(), mListTabBtn.end(), 
        [tabButton] (TabButton *tabbtn) { return tabbtn == tabButton; });
    if (ifind == mListTabBtn.end()) { return; }

    std::advance(ifind, 1);
    if (ifind == mListTabBtn.end()) {
        // 向前走两步
        std::advance(ifind, -2);
    }

    OnTabBtnPush(*ifind);

    resizeTabBtn();
}

void CustomTab::initUI()
{
    setStyle();
    connectSignals();

    ui.btn_restore->setVisible(false);
    for (int i = 0; i < 10; i++) {
        TabButton *tab_button = createTabButton();
        ui.tab_widget->layout()->addWidget(tab_button);
        mListTabBtn.push_back(tab_button);
    }

    QSpacerItem *item = new QSpacerItem(kLAYOUT_ITEM_WIDTH, 30, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    ui.tab_widget->layout()->addItem(item);
}

TabButton* CustomTab::createTabButton()
{
    std::for_each(mListTabBtn.begin(), mListTabBtn.end(), [] (TabButton *tabButton) {
        tabButton->SetPushStats(TabButton::PushStatus::Normal);
    });

    TabButton *tab_button = new TabButton(
        TabButton::sMAX_WIDTH, TabButton::sMAX_HIEGHT, ui.tab_widget);
	tab_button->SetText(tr("Loading..."));
    tab_button->SetPushStats(TabButton::PushStatus::Press);
    connect(tab_button, SIGNAL(OnClick(TabButton *)), this, SLOT(OnTabBtnPush(TabButton *)));
    connect(tab_button, SIGNAL(OnClose(TabButton *)), this, SLOT(OnTabClose(TabButton *)));

    return tab_button;
}

void CustomTab::resizeTabBtn()
{
    if (mListTabBtn.empty()) { return; }

 // 因为这个消息是Button发送过来的，不能直接删除Button对象，只能置为删除的标记
    int count = std::count_if(mListTabBtn.begin(), mListTabBtn.end(), 
                    [] (TabButton *tabButton) { return ! tabButton->GetDelete(); });

    QSize tab_widget_size = ui.tab_widget->size();
    QSize average_size((tab_widget_size.width()-kLAYOUT_ITEM_WIDTH)/count, 
                        tab_widget_size.height());
    std::for_each(mListTabBtn.begin(), mListTabBtn.end(), 
        [average_size](TabButton *tabButton) {  tabButton->Resize(average_size);  });
}

void CustomTab::setStyle()
{
    QFile file(k1KSTYLE.arg("style.qss"));
	if (file.open(QFile::ReadOnly)) {
		QString styleSheet = QLatin1String(file.readAll());
        // 1.4为圆角的最小值
        styleSheet = styleSheet.arg(4);
		qApp->setStyleSheet(styleSheet);
	}
	file.close();
}

void CustomTab::connectSignals()
{
	connect(ui.btn_close, SIGNAL(clicked()), this, SLOT(OnClose()));
	connect(ui.btn_min, SIGNAL(clicked()), this, SLOT(OnMin()));
	connect(ui.btn_max, SIGNAL(clicked()), this, SLOT(OnMax()));
	connect(ui.btn_restore, SIGNAL(clicked()), this, SLOT(OnRestor()));
}
