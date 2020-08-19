/****************************************************************************
**
** Copyright (C) 2020 liushixiong@flash.cn
** All rights reserved.
**
****************************************************************************/
#ifndef fcbrowser_tabbutton_h
#define fcbrowser_tabbutton_h

#include <QtWidgets/QPushButton>
#include <QtNetwork/QNetworkReply>
#include <QtGui/QPaintEvent>

#include <map>
#include <atomic>
#include <string>
#include <memory>

using std::map;
using std::wstring;
using std::shared_ptr;

/*! \brief	    TabButton
	\author	    liushixiong (liushixiong@flash.cn)
	\version	0.01
	\date		2020-04-29 10:27:29
	TabButton

    自定义标签，继承自QButton
*/
class TabButton : public QPushButton
{
    Q_OBJECT

public:
    typedef enum PushStatus
    {
        Normal,
        Enter,
        Leave,
        Press
    };

    static int sMAX_HIEGHT;
    static int sMAX_WIDTH;
    static int sMIN_WIDTH;

public:
    TabButton(int width, int height, QWidget *parent = nullptr);
    virtual ~TabButton();
    void SetPushStats(const PushStatus pushStatus);
    void SetText(const QString &title);
    void Resize(const QSize &size);
    void SetDelete(bool isDelete);
    bool GetDelete() const;
    void SetShowIndex(int index);
    int GetShowIndex() const;
    int GetID() const;
    bool operator==(const TabButton &tabButton);

protected:
    void paintEvent(QPaintEvent *paintEvent);
    void mousePressEvent(QMouseEvent *mouseEvent);
    void mouseReleaseEvent(QMouseEvent *mouseEvent);
    void mouseMoveEvent(QMouseEvent *mouseEvent);
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);

private:
    void initIcon();
    void initStatsMap();
    QString getElidedText(const QFont &font, const QString &text, int maxWidth);

signals:
    void OnClick(TabButton *);
    void OnClose(TabButton *);

private:
    PushStatus mPushStatus;
    bool   mCloseBtnIsHover;
    bool   mDelete;
    QColor mHighTextColor;
    QColor mNormalTextColor;
    QPixmap mNormalBK;
    QPixmap mHoverBK;
    QPixmap mPushBK;
    QPixmap mNormalBtnClose;
    QPixmap mHoverBtnClose;
    QPixmap mPushBtnClose;
    size_t mTextSize;
    QSize mBtnSize;
    QString mTitle;
    QFont mFont;
    QRect mBtnCloseRect;
    QRectF mTextRectF;

    QIcon mWebsiteIcon;
    QRect mWebsiteRect;
    QString mWebSiteIconPath;

    map<PushStatus, QPixmap *> mStatusMap;

    int mID;
    int mShowIndex;
    bool mDrawLine;

    static std::atomic_int sID;
};


#endif // fcbrowser_tabbutton_h