#include "formwait.h"

#include "zcyclprogress.h"

#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QApplication>

FormWait::FormWait(QWidget *parent, const QString &cyclPath) :
    QWidget(parent),
    m_centralFrame(NULL),
    m_cycl(NULL),
    m_textLabel(NULL)
{
    setAttribute(Qt::WA_TranslucentBackground);

    if (!QPixmap(cyclPath).isNull()) {
        m_cycl = new ZCyclProgress(cyclPath, 6, this);
    } else {
        m_cycl = new ZCyclProgress(":skins/skins/rom_loading.png", 6, this);
    }
    m_cycl->setAttribute(Qt::WA_TranslucentBackground);

    m_textLabel = new QLabel(this);
    setText(tr("please wait..."));
    m_textLabel->setStyleSheet(QString("color: white; background-color: transparent"));

    m_centralFrame = new QFrame(this);
    m_centralFrame->setStyleSheet(QString("background-color: rgb(0, 0, 0, %1); border-radius: 8; font-size: 14px").arg(int(255 * 0.75)));
    QHBoxLayout *innerLayout = new QHBoxLayout(this);
    innerLayout->addWidget(m_cycl);
    innerLayout->addWidget(m_textLabel);
    m_centralFrame->setLayout(innerLayout);

    QHBoxLayout *outerLayout = new QHBoxLayout(this);
    outerLayout->setMargin(0);
    outerLayout->addWidget(m_centralFrame);
    outerLayout->setAlignment(m_centralFrame, Qt::AlignCenter);
    setLayout(outerLayout);

    hide();
}

FormWait::~FormWait()
{
}

void FormWait::show()
{
    m_cycl->startAnimation();
    setVisible(true);
}

void FormWait::hide()
{
    m_cycl->stopAnimation();
    setVisible(false);
}

void FormWait::setText(const QString &text) {
     m_textLabel->setText(text);
     QFontMetrics m(m_textLabel->font());
     int width = m_cycl->width() + m.width(text);
     int height = m_cycl->height() > m_textLabel->height() ? m_cycl->height() : m_textLabel->height();
     resize(width + 24, height + 18);  // margin: 9 & spacing: 6
}
