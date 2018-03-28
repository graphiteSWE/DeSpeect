#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,g()
{
    ui->setupUi(this);
    ui->graphView->setScene(g.getGraphModel());
    ui->graphView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->relations->setModel(g.getRelationModel());
}

MainWindow::~MainWindow()
{
    delete ui;
}
