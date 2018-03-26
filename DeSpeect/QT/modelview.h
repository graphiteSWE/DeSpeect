#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <QMainWindow>

#include <iostream>
#include <QFileSystemModel>
#include <QGraphicsItem>
#include <QStandardItem>
#include <QTreeView>
#include <QFileDialog>

namespace Ui {
class ModelView;
}

class ModelView : public QMainWindow
{
    Q_OBJECT

public:
    QMap<QString, QGraphicsItem*> mappa;
    explicit ModelView(QWidget *parent = 0);
    ~ModelView();

public slots:
    void act(QStandardItem*);

private slots:
    void on_actionLoadVoice_triggered();

private:
    Ui::ModelView *ui;
    QStandardItemModel* a;
};

#endif // MODELVIEW_H
