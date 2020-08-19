#include "GifButton.h"

#include <QtCore/QDebug>
#include <QtGui/QPainter>
#include <QtGui/QMovie>
#include <QtGui/QPaintEvent>

const QString kRESOURCE1K = ":/MainWindow/res/image/%1"; 

GifButton::GifButton(QWidget *parent, 
					 const QString &gifPath) :
					QPushButton(parent), 
					mGifPath(gifPath),
					mGif(nullptr) {


	mGifFrame = QPixmap();

	mNormalBK	= QPixmap(kRESOURCE1K.arg("btn_login.png"));
	mHoverBK	= QPixmap(kRESOURCE1K.arg("btn_login_hover.png"));
	mPressBK	= QPixmap(kRESOURCE1K.arg("btn_login_push.png"));
	mDisabledBK = QPixmap(kRESOURCE1K.arg("btn_login_disabled.png"));
	mBtnStatus	= Normal;
	mTextColor	= Qt::black;

	if(! mGifPath.isEmpty()) {
		mGif = new QMovie(mGifPath, QByteArray(), this);
		connect(mGif, SIGNAL(frameChanged(int)), this, SLOT(OnIconChanged(int)));
		mGif->start();
	}

}
GifButton::~GifButton() {
	if (nullptr != mGif) {
		mGif->stop();
		delete mGif;
		mGif = nullptr;
	}
}

void GifButton::Stop() {
	mGifFrame = QPixmap();

	if (nullptr != mGif) {
		mGif->stop();
	}
	update();
}

void GifButton::Start() {
	if (nullptr != mGif) {
		mGif->start();
	}
	update();
}

void GifButton::SetText(const QString &text) {
	this->setText(text);
	update();
}

void GifButton::SetGifPath(const QString &path) {
	mGifPath = path;

	if (nullptr != mGif) {
		mGif->stop();
		delete mGif;
	}

	mGif = new QMovie(mGifPath, QByteArray(), this);
	connect(mGif, SIGNAL(frameChanged(int)), this, SLOT(OnIconChanged(int)));
}

QString GifButton::GifPath() const {
	return mGifPath;
}

void GifButton::SetEnabled(bool enable) {
	this->setEnabled(enable);
	update();
}

void GifButton::SetTextColor(QColor textColor) {
	mTextColor = textColor;
	update();
}

void GifButton::paintEvent(QPaintEvent *paintEvent) {
	const QRect rect = this->rect();

	QPainter painter(this);

	if (! this->isEnabled()) {
		painter.drawPixmap(rect, mDisabledBK);
	} else {
		if (Normal == mBtnStatus) {
			painter.drawPixmap(rect, mNormalBK);
		} else if (Hover == mBtnStatus) {
			painter.drawPixmap(rect, mHoverBK);
		} else if (Press == mBtnStatus) {
			painter.drawPixmap(rect, mPressBK);
		}
	}

	QString text = this->text();

    QFontMetrics fontWidth(this->font());  
    int width = fontWidth.width(text);
	int total_width = width;

	if (! mGifFrame.isNull()) {
		total_width += mGifFrame.width();
	}

	int text_distance = (rect.width()-total_width)/2;

	QRect text_rect(text_distance, 0, width, rect.height());
	
	QPen pen(mTextColor); 
	painter.setPen(pen);
	painter.drawText(text_rect, Qt::AlignHCenter | Qt::AlignVCenter, text);

	if (! mGifFrame.isNull()) {
		painter.drawPixmap(text_distance+width+2, 
						   (rect.height()-mGifFrame.height())/2, 
						   mGifFrame);
	}
}

void GifButton::enterEvent(QEvent *event) {
	mBtnStatus = Hover;
	update();
	QPushButton::enterEvent(event);
}

void GifButton::leaveEvent(QEvent *event) {
	mBtnStatus = Normal;
	update();
	QPushButton::leaveEvent(event);
}

void GifButton::mousePressEvent(QMouseEvent *event) {
	mBtnStatus = Press;
	update();
	QPushButton::mousePressEvent(event);
}

void GifButton::OnIconChanged(int) {
	QPixmap currFrame = mGif->currentPixmap();
	mGifFrame = QPixmap(currFrame.width(), currFrame.height());
	mGifFrame.fill(Qt::transparent);
	QPainter painter(&mGifFrame);
	painter.drawPixmap((mGifFrame.width()-currFrame.width()) / 2  ,
					   (mGifFrame.height()-currFrame.height()) / 2, currFrame);
	update();
}
