#include "dialogwait.h"
#include "zcyclprogress.h"

#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QTimer>
#include <QPainter>

DialogWait::DialogWait(QWidget *parent, bool animation, bool closeBtnHint) :
    QDialog(parent, Qt::FramelessWindowHint),
    animationHint(animation),
    isAltF4Flag(false),
    cycl(NULL), labelText(NULL), closeBtn(NULL),
    alpha(int(255 * 0.75))
{
    setAttribute(Qt::WA_TranslucentBackground);

    // cycl
    cycl = new ZCyclProgress(":/images/loading.png", 6, this);
    cycl->setFixedSize(QPixmap(":/images/loading.png").size());

    // text
    labelText = new QLabel(this);
    labelText->setStyleSheet("color: white;");

    // close btn
    closeBtn = new QPushButton(tr("Cancel"), this);
    closeBtn->setObjectName("closeBtn");
    closeBtn->setStyleSheet("#closeBtn {background-color: transparent; border: none; font: 12px; color: #33B6FF;}");
    closeBtn->setMinimumSize(40, 15);
    closeBtn->setMaximumSize(40, 15);
    connect(closeBtn, SIGNAL(clicked()), SIGNAL(signal_cancel()));
    connect(closeBtn, SIGNAL(clicked()), SLOT(close()));
    closeBtn->setVisible(closeBtnHint);

    // layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(6);
    layout->setContentsMargins(9, 9, 9, 9);
    layout->addItem(new QSpacerItem(0, 40, QSizePolicy::Expanding, QSizePolicy::Preferred));
    layout->addWidget(cycl);
    layout->addWidget(labelText);
    if (closeBtnHint) {
        layout->addItem(new QSpacerItem(0, 40, QSizePolicy::Expanding, QSizePolicy::Preferred));
    }
    layout->addWidget(closeBtn);
    layout->setAlignment(closeBtn, Qt::AlignCenter);
    layout->addItem(new QSpacerItem(0, 40, QSizePolicy::Expanding, QSizePolicy::Preferred));
    setLayout(layout);

    installEventFilter(this);
    closeBtn->installEventFilter(this);

    setStyleSheet("QDialog {border: none;}");
}

void DialogWait::alert(QWidget *parent, const QString &content, const QString &pixmap, bool animationStart, quint64 ms) {
    DialogWait *dw = new DialogWait(parent, animationStart);
    dw->setText(content);
    dw->setCyclPixmap(pixmap);
    QTimer::singleShot(ms, dw, SLOT(deleteLater()));
    dw->show();
}

void DialogWait::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QColor color(0, 0, 0, alpha);
    painter.setPen(color);
    painter.setBrush(QBrush(color));
//    painter.drawRoundRect(0, 0, width(), height(), 8, 8);
    painter.drawRoundedRect(0, 0, width(), height(), 8.0, 8.0);  // NOTE: 达不到圆角效果

    QDialog::paintEvent(e);
}

void DialogWait::keyPressEvent(QKeyEvent *e) {
    e->ignore();
}

bool DialogWait::eventFilter(QObject *obj, QEvent *event) {
    if(obj->isWidgetType()) {
        if (obj == closeBtn) {
            if (event->type() == QEvent::Enter) {
                closeBtn->setText(tr("[Cancel]"));
            } else if (event->type() == QEvent::Leave) {
                closeBtn->setText(tr("Cancel"));
            }
        }

        switch(event->type()) {
        case QEvent::Close: {
            if(isAltF4Flag){
                isAltF4Flag = false;
                event->ignore();
                return true;
            }
            break;
        }
        case QEvent::KeyPress: {
            if(((QKeyEvent*)event)->key() == Qt::Key_F4 || (((QKeyEvent*)event)->modifiers() == Qt::AltModifier)) {
                isAltF4Flag = true;
            }
            break;
        }
        default: break;
        }
    }
    return QObject::eventFilter(obj,event);
}

void DialogWait::exec() {
    if (animationHint)
        cycl->startAnimation();
    QDialog::exec();
}

void DialogWait::show() {
    if (animationHint)
        cycl->startAnimation();
    QDialog::show();
}

void DialogWait::hide() {
    cycl->stopAnimation();
    QDialog::hide();
}

void DialogWait::setText(const QString &text) {
    labelText->setText(text);
}

void DialogWait::setCyclPixmap(const QString &pixmap) {
    cycl->setCyclPixmap(pixmap);
    cycl->setFixedSize(QPixmap(pixmap).size());
}

void DialogWait::setAlpha(int value) {
    alpha = value;
}

ZCyclProgress *DialogWait::getCycl() {
    return cycl;
}

QPushButton *DialogWait::getCloseBtn() {
    return closeBtn;
}
