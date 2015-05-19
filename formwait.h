#ifndef FORMWAIT_H
#define FORMWAIT_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class FormWait;
}

class QFrame;
class QLabel;
class ZCyclProgress;
class FormWait : public QWidget
{
    Q_OBJECT

public:
    explicit FormWait(QWidget *parent = 0, const QString &cyclPath = "");
    ~FormWait();

    void show();
    void hide();

    void setText(const QString &text);

private:
    QFrame *m_centralFrame;
    ZCyclProgress *m_cycl;
    QLabel *m_textLabel;
};

#endif // FORMWAIT_H
