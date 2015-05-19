#ifndef DIALOGWAIT_H
#define DIALOGWAIT_H

#include <QDialog>
#include <QPaintEvent>

class QLabel;
class QPushButton;
class ZCyclProgress;
class DialogWait : public QDialog
{
    Q_OBJECT

    ZCyclProgress *cycl;
    QLabel *labelText;
    QPushButton *closeBtn;
    bool isAltF4Flag;
    bool animationHint;
    int alpha;

signals:
    void signal_cancel();

public:
    explicit DialogWait(QWidget *parent = 0, bool animation = true, bool closeBtnHint = false);
    static void alert(QWidget *parent, const QString &content, const QString &pixmap = "", bool animationStart = true, quint64 ms = 2000);

    void setCyclPixmap(const QString &);
    void setAlpha(int value);
    ZCyclProgress *getCycl();
    QPushButton *getCloseBtn();

protected:
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *e);
    bool eventFilter(QObject *obj, QEvent *event);

public slots:
    void exec();
    void show();
    void hide();
    void setText(const QString &text);

};

#endif // DIALOGWAIT_H
