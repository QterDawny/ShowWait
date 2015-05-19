#ifndef ZCYCLPROGRESS_H
#define ZCYCLPROGRESS_H

#include <QLabel>
#include <QPixmap>

///
/// \brief The ZCyclProgress class
/// setParent()可将旋转图片移到相应的Widget上, setParent后刻show();
///
class ZCyclProgress : public QLabel
{
    Q_OBJECT
signals:
    void runMinLoopsEnough();

public:
    explicit ZCyclProgress(const QString &pixmap, uint angleInterval = 6, QWidget *parent = 0);

    void setMinLoops(int loops = 3);

public slots:
    void startAnimation(int interval = 25);
    void stopAnimation();

    void setCyclPixmap(const QPixmap &);

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *event);

private:
    int timerID;
    int minLoops;
    int angle;
    QPixmap m_pixmap;
    qreal m_rotation;
};

#endif // ZCYCLPROGRESS_H
