#include "mainwindow.h"
#include "ui_mainwindow.h"
//moc class
MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,g()
{
    ui->setupUi(this);
    g.linkGraphModel(ui->graphicsView);
    g.linkRelationModel(ui->listView);
}

MainWindow::~MainWindow()
{
    delete ui;
}
