#include "modelview.h"
#include "ui_modelview.h"

ModelView::ModelView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ModelView)
{
    ui->setupUi(this);

    a=new QStandardItemModel();
    ui->listView->setModel(a);
    QGraphicsScene* scena=new QGraphicsScene();

    QStandardItem* c=new QStandardItem("Normalize");
    QGraphicsItemGroup* item=new QGraphicsItemGroup();
    QGraphicsItem * cosa = new QGraphicsEllipseItem(0, 0, 20, 20);
    item->addToGroup(cosa);
    item->addToGroup(new QGraphicsEllipseItem(40, 40, 20, 20));
    item->addToGroup(new QGraphicsEllipseItem(80, 80, 20, 20));
    item->hide();
    mappa.insert("Normalize",item);
    scena->addItem(item);
    c->setCheckable(true);
    c->setEditable(false);
    c->setCheckState(Qt::Unchecked);
    connect(a,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(act(QStandardItem*)));
    a->appendRow(c);
    ui->graphicsView->setScene(scena);
}

ModelView::~ModelView()
{
    delete ui;
}

void ModelView::act(QStandardItem *focused)
{
    std::cout<<focused->text().toStdString()<<" "<<focused->checkState()<<std::endl;
    auto t=mappa.find(focused->text());
    if(focused->checkState()==Qt::Checked)
    (*t)->show();
    else
    (*t)->hide();
}

void ModelView::on_actionLoadVoice_triggered()
{
    QFileSystemModel *model = new QFileSystemModel();
    model->setRootPath(QDir::currentPath());
    QTreeView *tree = new QTreeView(this);
    tree->setModel(model);
    tree->setRootIndex(model->index(QDir::currentPath()));
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return;
    return;
}
