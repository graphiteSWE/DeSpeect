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
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    g.linkRelationModel(ui->listView);
}

MainWindow::~MainWindow()
{
    delete ui;
}
