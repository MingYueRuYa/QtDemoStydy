#include "qmyextlabel.h"
#include "qmyextlabelplugin.h"

#include <QtPlugin>

QMyExtLabelPlugin::QMyExtLabelPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void QMyExtLabelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool QMyExtLabelPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *QMyExtLabelPlugin::createWidget(QWidget *parent)
{
    return new QMyExtLabel(parent);
}

QString QMyExtLabelPlugin::name() const
{
    return QLatin1String("QMyExtLabel");
}

QString QMyExtLabelPlugin::group() const
{
    return QLatin1String("My Custom Control");
}

QIcon QMyExtLabelPlugin::icon() const
{
    return QIcon();
}

QString QMyExtLabelPlugin::toolTip() const
{
    return QLatin1String("");
}

QString QMyExtLabelPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool QMyExtLabelPlugin::isContainer() const
{
    return false;
}

QString QMyExtLabelPlugin::domXml() const
{
    return QLatin1String("<widget class=\"QMyExtLabel\" name=\"qMyExtLabel\">\n</widget>\n");
}

QString QMyExtLabelPlugin::includeFile() const
{
    return QLatin1String("qmyextlabel.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qmyextlabelplugin, QMyExtLabelPlugin)
#endif // QT_VERSION < 0x050000
