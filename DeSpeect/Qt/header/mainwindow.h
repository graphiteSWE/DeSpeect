#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <graphmanager.h>

//just a moc class to test the Ui
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    GraphManager g;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
