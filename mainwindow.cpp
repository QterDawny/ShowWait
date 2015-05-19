#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialogwait.h"
#include "formwait.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    DialogWait dlg(this, true, true);
    dlg.setFixedWidth(250);
    dlg.setText("xxxxxxxxxx");
    QTimer::singleShot(5000, &dlg, SLOT(accept()));
    dlg.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    DialogWait::alert(this, "xxxxxxxxxxxxxx", ":/images/success_icon.png");
}

void MainWindow::on_pushButton_2_clicked()
{
    static FormWait *form = NULL;
    if (NULL == form) {
        form = new FormWait(this);
    }
    QTimer::singleShot(5000, form, SLOT(close()));
    form->setFixedSize(size());
    form->show();
}
