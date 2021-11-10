#include "qmyextlabel.h"

#include <QPainter>
#include <QPainterPath>

QMyExtLabel::QMyExtLabel(QWidget *parent) :
    QLabel(parent)
{
    this->setText(tr("QMyExtLabel"));
}

bool QMyExtLabel::autoElideText() const
{
    return m_autoElideText;
}

void QMyExtLabel::SetAutoElideText(bool autoElideText)
{
    m_autoElideText = autoElideText;
}

void QMyExtLabel::enterEvent(QEvent *ev)
{
    __super::enterEvent(ev);

    emit MouseEnter();
}

void QMyExtLabel::leaveEvent(QEvent *ev)
{
    __super::leaveEvent(ev);

    emit MouseLeave();
}

void QMyExtLabel::mousePressEvent(QMouseEvent *ev)
{
    __super::mousePressEvent(ev);

    m_bMousePressed = true;
}

void QMyExtLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    __super::mouseReleaseEvent(ev);

    if (m_bMousePressed)
    {
        m_bMousePressed = false;
        emit clicked();
    }
}

void QMyExtLabel::resizeEvent(QResizeEvent *ev)
{
    __super::resizeEvent(ev);

    if (m_autoElideText) {
        QString strText = _ElideText();
        setText(strText);
    }
    else {
        setText(m_rawText);
    }
}

void QMyExtLabel::paintEvent(QPaintEvent * event)
{
    if (m_textStroke)
    {
        _StrokeText(text(), alignment());
    }
    else
    {
       _PaintText();
    }
}

QString QMyExtLabel::_ElideText()
{
    // 去掉margin的距离
    QMargins mergin = this->contentsMargins();

    QFont font = this->font();
    QFontMetrics fm(font);
    QString strElideText = fm.elidedText(m_rawText, m_textElideMode, this->width() - mergin.right() - mergin.left());

    return strElideText;
}

void QMyExtLabel::_StrokeText(const QString &strText, Qt::Alignment align)
{
    // 这块代码需要大家仔细的琢磨下，思路还是很常见的。
    QMargins margins = this->contentsMargins();
    QRect rcSize = this->rect();
    rcSize.adjust(margins.left(), margins.top(), -margins.right(), -margins.bottom());

    QFont font = this->font();
    QFontMetrics metrics(font);
    int len = metrics.width(strText);

    int px = rcSize.left();
    if (align & Qt::AlignmentFlag::AlignHCenter)
    {
      px = (len - rcSize.width()) / 2 + margins.left();
    }
    else if (align & Qt::AlignmentFlag::AlignRight)
    {
      int width = rcSize.width();
      px = width - len + margins.left();
    }
    if (px < 0)
    {
      px = -px;
    }

    int py = (rcSize.height() - metrics.height()) / 2 + metrics.ascent() + margins.top();
    if (align & Qt::AlignmentFlag::AlignTop)
    {
      py = metrics.ascent() + margins.top();
    }
    else if (align & Qt::AlignmentFlag::AlignBottom)
    {
      py = rcSize.height() - metrics.height() + metrics.ascent() + margins.top();
    }
    if (py < 0)
    {
      py = -py;
    }

    QPen pen;
    pen.setColor(m_borderColor);
    pen.setWidth(m_borderSize);

    QPainterPath path;
    path.addText(px, py, font, strText);

    QPainter painter(this);
    painter.save();
    painter.setRenderHints(QPainter::Antialiasing);
    painter.strokePath(path, pen);
    painter.drawPath(path);
    painter.fillPath(path, QBrush(m_textColor));
    painter.restore();
}

void QMyExtLabel::_PaintText()
{
    QPen pen;
    pen.setColor(m_textColor);

    QPainter painter(this);
    painter.save();
    painter.setPen(pen);
    painter.setFont(this->font());
    painter.drawText(this->rect(), this->text(), this->alignment());
    painter.restore();
}

QString QMyExtLabel::rawText() const
{
    return m_rawText;
}

void QMyExtLabel::SetRawText(const QString &strRawText)
{
    m_rawText = strRawText;
    setText(m_rawText);

    update();
}

Qt::TextElideMode QMyExtLabel::textElideMode() const
{
    return m_textElideMode;
}

void QMyExtLabel::SetTextElideMode(Qt::TextElideMode textElideMode)
{
    m_textElideMode = textElideMode;

    if (m_autoElideText) {
        QString strText = _ElideText();
        setText(strText);
    }
    else {
        setText(m_rawText);
    }
    update();
}

int QMyExtLabel::borderSize() const
{
    return m_borderSize;
}

void QMyExtLabel::SetBorderSize(int borderSize)
{
    m_borderSize = borderSize;
    update();
}

bool QMyExtLabel::textStroke() const
{
    return m_textStroke;
}

void QMyExtLabel::SetTextStroke(bool textStroke)
{
    m_textStroke  = textStroke;

    update();
}

QColor QMyExtLabel::textColor() const
{
    return m_textColor;
}

void QMyExtLabel::SetTextColor(const QColor &textColor)
{
    m_textColor = textColor;

    update();
}

QColor QMyExtLabel::borderColor() const
{
    return m_borderColor;
}

void QMyExtLabel::SetBorderColor(const QColor &borderColor)
{
    m_borderColor = borderColor;
    update();
}
