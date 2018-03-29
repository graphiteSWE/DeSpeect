#include "mainwindow.h"
#include "ui_mainwindow.h"
//moc class
MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,g()
{
    ui->setupUi(this);
    g.linkGraphModel(ui->graphView);
    ui->graphView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    g.linkRelationModel(ui->relations);
}

MainWindow::~MainWindow()
{
    delete ui;
}
