#include "zcyclprogress.h"
#include <QPainter>
#include <QTimerEvent>

ZCyclProgress::ZCyclProgress(const QString &pixmap, uint angleInterval, QWidget *parent) :
    QLabel(parent),
    minLoops(3), m_rotation(0.0), timerID(0), angle(angleInterval)
{
    m_pixmap = QPixmap(pixmap);
    setMinimumSize(m_pixmap.size());
    setMaximumSize(m_pixmap.size());
}

void ZCyclProgress::timerEvent(QTimerEvent * event) {
    if(timerID == event->timerId()){
        m_rotation += angle;
        if (m_rotation >= 360) {
            m_rotation -= 360;
        }
        update();
    }
}

void ZCyclProgress::paintEvent(QPaintEvent * /*event*/) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::Antialiasing);

    QPointF center(m_pixmap.width() / qreal(2), m_pixmap.height() / qreal(2));

    painter.translate(center);
    painter.rotate(m_rotation);
    painter.translate(-center);

    painter.drawPixmap(QPointF(0, 0), m_pixmap);
}


void ZCyclProgress::setMinLoops(int loops) {
    minLoops = loops;
}

void ZCyclProgress::startAnimation(int interval) {
    if(0 == timerID) {
        timerID = startTimer(interval);
    }
    show();
}

void ZCyclProgress::stopAnimation() {
    killTimer(timerID);
    timerID = 0;
    hide();
}

void ZCyclProgress::setCyclPixmap(const QPixmap &pixmap) {
    m_pixmap = pixmap;
    repaint();
}
