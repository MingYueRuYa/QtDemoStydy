#ifndef gifbutton_h
#define gifbutton_h

#include <QtWidgets/QPushButton>

class QEvent;
class QMovie;
class QMoveEvent;
class QPaintEvent;

class GifButton : public QPushButton
{
	Q_OBJECT

	enum BtnStatus {
		Normal,
		Hover,
		Press,
		Disabled
	};

public:
	GifButton(QWidget *parent, const QString &gifPath = "");
	~GifButton();
	void Stop();
	void Start();
	void SetText(const QString &text);
	void SetGifPath(const QString &path);
	QString GifPath() const;
	void SetEnabled(bool enable);
	void SetTextColor(QColor textColor);

protected:
	void paintEvent(QPaintEvent *paintEvent) override;
	void enterEvent(QEvent *event) override;
	void leaveEvent(QEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;

protected slots:
	void OnIconChanged(int);

private:
	bool mStop;
	QColor mTextColor;
	QString mGifPath;
	QMovie *mGif;
	QPixmap mGifFrame;
	QPixmap mNormalBK;
	QPixmap mHoverBK;
	QPixmap mPressBK;
	QPixmap mDisabledBK;
	BtnStatus mBtnStatus;
};

#endif // gifbutton_h