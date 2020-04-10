#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QStandardItemModel>

#include "viewer/node.hpp"
#include "myglwidget.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void generateObjectTree();
    void setTimer();

    void setGLWidget(MyGLWidget* glWidget);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *treeViewModel;
    MyGLWidget *glWidget;

public slots:
    void frame();
};

#endif // MAINWINDOW_HPP
