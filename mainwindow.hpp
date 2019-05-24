#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QStandardItemModel>

#include "viewer/node.hpp"

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

private:
    Ui::MainWindow *ui;
    QStandardItemModel *treeViewModel;

    void populateObjectTree(Node* node, QStandardItem* parent);

public slots:
    void frame();
};

#endif // MAINWINDOW_HPP
