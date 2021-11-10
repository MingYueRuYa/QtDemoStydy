#ifndef QMYEXTLABEL_H
#define QMYEXTLABEL_H

#include <QLabel>
#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT QMyExtLabel : public QLabel
{
    Q_OBJECT
    // 省略号的属性
    Q_PROPERTY(bool autoElideText READ autoElideText WRITE SetAutoElideText)
    // 保留的源字符串
    Q_PROPERTY(QString rawText READ rawText WRITE SetRawText)
    // 省略号的位置（左边，居中，右边）
    Q_PROPERTY(Qt::TextElideMode textElideMode READ textElideMode WRITE SetTextElideMode)
    // 描边的边大小
    Q_PROPERTY(int borderSize READ borderSize WRITE SetBorderSize)
    // 是否支持描边
    Q_PROPERTY(bool textStroke READ textStroke WRITE SetTextStroke)
    // 描边的颜色
    Q_PROPERTY(QColor borderColor READ borderColor WRITE SetBorderColor)
    // 文字的颜色
    Q_PROPERTY(QColor textColor READ textColor WRITE SetTextColor)

public:
    QMyExtLabel(QWidget *parent = 0);

    bool autoElideText() const;
    void SetAutoElideText(bool autoElideText);

    QString rawText() const;
    void SetRawText(const QString &strRawText);

    Qt::TextElideMode textElideMode() const;
    void SetTextElideMode(Qt::TextElideMode textElideMode);

    int borderSize() const;
    void SetBorderSize(int borderSize);

    bool textStroke() const;
    void SetTextStroke(bool textStroke);

    QColor textColor() const;
    void SetTextColor(const QColor &textColor);

    QColor borderColor() const;
    void SetBorderColor(const QColor &borderColor);

protected:
    virtual void enterEvent(QEvent *ev);
    virtual void leaveEvent(QEvent *ev);
    virtual void mousePressEvent(QMouseEvent *ev);
    virtual void mouseReleaseEvent(QMouseEvent *ev);
    virtual void resizeEvent(QResizeEvent *ev);
    virtual void paintEvent(QPaintEvent * event);

signals:
    void clicked();
    void MouseEnter();
    void MouseLeave();

private:
    QString _ElideText();
    void _StrokeText(const QString &strText, Qt::Alignment align);
    void _PaintText();

private:
    bool m_textStroke    = false;
    bool m_bMousePressed = true;
    bool m_autoElideText = true;
    int m_borderSize     = 0;
    QColor m_borderColor = QColor(0,0,0);
    QColor m_textColor   = QColor(0,255,255);
    QString m_rawText    = tr("This is test Label Text");
    Qt::TextElideMode m_textElideMode = Qt::ElideMiddle;
};

#endif
